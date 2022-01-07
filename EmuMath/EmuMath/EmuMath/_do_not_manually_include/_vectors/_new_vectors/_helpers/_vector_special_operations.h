#ifndef EMU_MATH_NEW_VECTOR_SPECIAL_OPERATIONS_H_INC_
#define EMU_MATH_NEW_VECTOR_SPECIAL_OPERATIONS_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../../EmuCore/Functors/Arithmetic.h"

// CONTAINS:
// --- dot
// --- square_magnitude
// --- magnitude_constexpr
// --- magnitude
// --- normalise_constexpr
// --- normalise
// --- angle_cos_constexpr
// --- angle_cos
// --- angle
// --- cross_3d
// --- square_distance
// --- distance
// --- distance_constexpr

namespace EmuMath::Helpers
{
#pragma region DOT_FUNCS
	/// <summary>
	/// <para> Calculates the dot-product of the provided two EmuMath Vectors, outputting the result as the provided Out_ type. </para>
	/// <para> Out_ will default to the preferred_floating_point of vector_a_ if not provided. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output the dot-product as, defaulting to vector_a_'s preferred_floating_point.</typeparam>
	/// <param name="vector_a_">: EmuMath Vector `a` for finding the dot product.</param>
	/// <param name="vector_b_">: EmuMath Vector `b` for finding the dot product.</param>
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
	/// <param name="vector_a_">: EmuMath Vector `a` for finding the dot product.</param>
	/// <param name="vector_b_">: EmuMath Vector `b` for finding the dot product.</param>
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
	/// <param name="vector_">: EmuMath Vector to calculate the square magnitude of.</param>
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
	/// <param name="vector_">: EmuMath Vector to calculate the square magnitude of.</param>
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
	/// <param name="vector_">: EmuMath Vector to calculate the magnitude of.</param>
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
	/// <para> BeginIndex_: Inclusive index at which to start reading from the passed Vector for calculations. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading from the passed Vector for calculations. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output the magnitude as, defaulting to the passed Vector's preferred_floating_point.</typeparam>
	/// <param name="vector_">: EmuMath Vector to calculate the magnitude of.</param>
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
	/// <param name="vector_">: EmuMath Vector to calculate the magnitude of.</param>
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
	/// <para> BeginIndex_: Inclusive index at which to start reading from the passed Vector for calculations. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading from the passed Vector for calculations. </para>
	/// <para> For a guarantee to produce a compile-time result if possible, use `vector_magnitude_constexpr` instead. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output the magnitude as, defaulting to the passed Vector's preferred_floating_point.</typeparam>
	/// <param name="vector_">: EmuMath Vector to calculate the magnitude of.</param>
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

#pragma region NORMALISE_CONSTEXPR_FUNCS
	/// <summary>
	/// <para> Outputs a normalised form of the provided in_vector_, built as an EmuMath Vector using the provided OutSize_ and OutT_ arguments. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to calculate the normalised form of.</param>
	/// <returns>Normalised form of the passed EmuMath Vector.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_normalise_constexpr(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, OutSize_, OutT_>(in_vector_);
	}
	template<typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_normalise_constexpr(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, InSize_, OutT_>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point> new_vector_normalise_constexpr
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, OutSize_, out_arg>(in_vector_);
	}
	template<typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point> new_vector_normalise_constexpr
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, InSize_, out_arg>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a normalised form of the provided in_vector_, via the provided out_vector_. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="in_vector_">: EmuMath Vector to calculate the normalised form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_normalise_constexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr>(out_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a normalised form of the provided in_vector_, built as an EmuMath Vector using the provided OutSize_ and OutT_ arguments. </para>
	/// <para> Only indices in the provided range will be normalised; indices outside of said range will be copied without modification. </para>
	/// <para> BeginIndex_: Inclusive index at which to start normalising elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop normalising elements. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to calculate the normalised form of.</param>
	/// <returns>Normalised form of the passed EmuMath Vector.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_normalise_range_constexpr(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, OutSize_, OutT_>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_normalise_range_constexpr(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, InSize_, OutT_>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point> new_vector_normalise_range_constexpr
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, OutSize_, out_arg>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point> new_vector_normalise_range_constexpr
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, InSize_, out_arg>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a normalised form of the provided in_vector_, via the provided out_vector_. </para>
	/// <para> Only indices in the provided range will be normalised; indices outside of said range will be copied without modification. </para>
	/// <para> BeginIndex_: Inclusive index at which to start normalising elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop normalising elements. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="in_vector_">: EmuMath Vector to calculate the normalised form of.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_normalise_range_constexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_>(out_vector_, in_vector_);
	}
#pragma endregion

#pragma region NORMALISE_FUNCS
	/// <summary>
	/// <para> Outputs a normalised form of the provided in_vector_, built as an EmuMath Vector using the provided OutSize_ and OutT_ arguments. </para>
	/// <para> For a guarantee to produce a compile-time result if possible, use `vector_normalise_constexpr` instead. </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to calculate the normalised form of.</param>
	/// <returns>Normalised form of the passed EmuMath Vector.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_normalise(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, OutSize_, OutT_>(in_vector_);
	}
	template<typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_normalise(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, InSize_, OutT_>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point> new_vector_normalise
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, OutSize_, out_arg>(in_vector_);
	}
	template<typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point> new_vector_normalise
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, InSize_, out_arg>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a normalised form of the provided in_vector_, via the provided out_vector_. </para>
	/// <para> For a guarantee to produce a compile-time result if possible, use `vector_normalise_constexpr` instead. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="in_vector_">: EmuMath Vector to calculate the normalised form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_normalise(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt>(out_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a normalised form of the provided in_vector_, built as an EmuMath Vector using the provided OutSize_ and OutT_ arguments. </para>
	/// <para> Only indices in the provided range will be normalised; indices outside of said range will be copied without modification. </para>
	/// <para> BeginIndex_: Inclusive index at which to start normalising elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop normalising elements. </para>
	/// <para> For a guarantee to produce a compile-time result if possible, use `vector_normalise_range_constexpr` instead. </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to calculate the normalised form of.</param>
	/// <returns>Normalised form of the passed EmuMath Vector.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_normalise_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, BeginIndex_, EndIndex_, OutSize_, OutT_>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_normalise_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, BeginIndex_, EndIndex_, InSize_, OutT_>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point> new_vector_normalise_range
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, BeginIndex_, EndIndex_, OutSize_, out_arg>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point> new_vector_normalise_range
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::NewVector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, BeginIndex_, EndIndex_, InSize_, out_arg>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a normalised form of the provided in_vector_, via the provided out_vector_. </para>
	/// <para> Only indices in the provided range will be normalised; indices outside of said range will be copied without modification. </para>
	/// <para> BeginIndex_: Inclusive index at which to start normalising elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop normalising elements. </para>
	/// <para> For a guarantee to produce a compile-time result if possible, use `vector_normalise_range_constexpr` instead. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="in_vector_">: EmuMath Vector to calculate the normalised form of.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_normalise_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, BeginIndex_, EndIndex_>(out_vector_, in_vector_);
	}
#pragma endregion

#pragma region ANGLE_FUNCS
	/// <summary>
	/// <para> Calculates the cosine of the angle between the two passed EmuMath Vectors. </para>
	/// <para> Radians_: If true, output will be in radians; otherwise, it will be in degrees. Defaults to true. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="vector_a_">First EmuMath Vector of the two to find the cosine of the angle between.</param>
	/// <param name="vector_b_">Second EmuMath Vector of the two to find the cosine of the angle between.</param>
	/// <returns>Cosine of the angle between the two provided EmuMath Vectors, in radians or degrees depending on the Radians_ arg.</returns>
	template<typename Out_, bool Radians_ = true, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline Out_ new_vector_angle_cos_constexpr(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, const EmuMath::NewVector<SizeB_, TB_>& vector_b_)
	{
		return _vector_underlying::_vector_angle_cos<EmuCore::do_sqrt_constexpr, Out_, Radians_>(vector_a_, vector_b_);
	}
	template<bool Radians_ = true, typename TA_, std::size_t SizeA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point new_vector_angle_cos_constexpr
	(
		const EmuMath::NewVector<SizeA_, TA_>& vector_a_,
		const EmuMath::NewVector<SizeB_, TB_>& vector_b_
	)
	{
		using out_type_arg = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_angle_cos<EmuCore::do_sqrt_constexpr, out_type_arg, Radians_>(vector_a_, vector_b_);
	}

	/// <summary>
	/// <para> Calculates the cosine of the angle between the two passed EmuMath Vectors. </para>
	/// <para> Radians_: If true, output will be in radians; otherwise, it will be in degrees. Defaults to true. </para>
	/// <para> For a guarantee to produce a compile-time result if possible, use `vector_angle_cos_constexpr` instead. </para>
	/// </summary>
	/// <param name="vector_a_">First EmuMath Vector of the two to find the cosine of the angle between.</param>
	/// <param name="vector_b_">Second EmuMath Vector of the two to find the cosine of the angle between.</param>
	/// <returns>Cosine of the angle between the two provided EmuMath Vectors, in radians or degrees depending on the Radians_ arg.</returns>
	template<typename Out_, bool Radians_ = true, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline Out_ new_vector_angle_cos(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, const EmuMath::NewVector<SizeB_, TB_>& vector_b_)
	{
		return _vector_underlying::_vector_angle_cos<EmuCore::do_sqrt, Out_, Radians_>(vector_a_, vector_b_);
	}
	template<bool Radians_ = true, typename TA_, std::size_t SizeA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point new_vector_angle_cos
	(
		const EmuMath::NewVector<SizeA_, TA_>& vector_a_,
		const EmuMath::NewVector<SizeB_, TB_>& vector_b_
	)
	{
		using out_type_arg = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_angle_cos<EmuCore::do_sqrt, out_type_arg, Radians_>(vector_a_, vector_b_);
	}

	/// <summary>
	/// <para> Calculates the angle between the two passed EmuMath Vectors. </para>
	/// <para> Radians_: If true, output will be in radians; otherwise, it will be in degrees. Defaults to true. </para>
	/// </summary>
	/// <param name="vector_a_">First EmuMath Vector of the two to find the angle between.</param>
	/// <param name="vector_b_">Second EmuMath Vector of the two to find the angle between.</param>
	/// <returns>Angle between the two provided EmuMath Vectors, in radians or degrees depending on the Radians_ arg.</returns>
	template<typename Out_, bool Radians_ = true, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline Out_ new_vector_angle(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, const EmuMath::NewVector<SizeB_, TB_>& vector_b_)
	{
		return _vector_underlying::_vector_angle<EmuCore::do_sqrt, EmuCore::do_acos, Out_, Radians_>(vector_a_, vector_b_);
	}
	template<bool Radians_ = true, typename TA_, std::size_t SizeA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point new_vector_angle
	(
		const EmuMath::NewVector<SizeA_, TA_>& vector_a_,
		const EmuMath::NewVector<SizeB_, TB_>& vector_b_
	)
	{
		using out_type_arg = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_angle<EmuCore::do_sqrt, EmuCore::do_acos, out_type_arg, Radians_>(vector_a_, vector_b_);
	}
#pragma endregion

#pragma region CROSS_PRODUCT_3D_FUNCS
	/// <summary>
	/// <para> Outputs the 3D cross product of the two passed EmuMath Vectors, using theoretical indices 0, 1, 2. </para>
	/// <para> Listed output will be provided for output Vectors which contain at least up to that element: </para>
	/// <para> [0] = (a_[1] * b_[2]) - (a_[2] * b_[1]) </para>
	/// <para> [1] = (a_[2] * b_[0]) - (a_[0] * b_[2]) </para>
	/// <para> [2] = (a_[0] * b_[1]) - (a_[1] * b_[0]) </para>
	/// <para> [...] = default, or implied 0 if default construction is not possible. </para>
	/// <para> Unlike most EmuMath Vector functions, if no OutSize_ is provided this will always default to 3 instead of SizeA_, due to the meaning of cross products. </para>
	/// </summary>
	/// <param name="a_">: EmuMath Vector appearing as `a_` in the listed calculations.</param>
	/// <param name="b_">: EmuMath Vector appearing as `b_` in the listed calculations.</param>
	/// <returns>3D cross product of EmuMath Vectors a_ and b_, using theoretical indices 0, 1, 2.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_cross_3d(const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, OutSize_, OutT_, 0, 1, 2, 0, 1, 2>(a_, b_);
	}

	template<typename OutT_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<3, OutT_> new_vector_cross_3d(const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, 3, OutT_, 0, 1, 2, 0, 1, 2>(a_, b_);
	}

	template<std::size_t OutSize_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point> new_vector_cross_3d
	(
		const EmuMath::NewVector<SizeA_, TA_>& a_,
		const EmuMath::NewVector<SizeB_, TB_>& b_
	)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, OutSize_, a_fp, 0, 1, 2, 0, 1, 2>(a_, b_);
	}

	template<typename TA_, std::size_t SizeA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<3, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point> new_vector_cross_3d
	(
		const EmuMath::NewVector<SizeA_, TA_>& a_,
		const EmuMath::NewVector<SizeB_, TB_>& b_
	)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, 3, a_fp, 0, 1, 2, 0, 1, 2>(a_, b_);
	}

	/// <summary>
	/// <para> Outputs the 3D cross product of the two passed EmuMath Vectors, using theoretical indices I0_, I1_, I2_. </para>
	/// <para> Listed output will be provided for output Vectors which contain at least up to that element: </para>
	/// <para> [0] = (a_[I1_] * b_[I2_]) - (a_[I2_] * b_[I1_]) </para>
	/// <para> [1] = (a_[I2_] * b_[I0_]) - (a_[I0_] * b_[I2_]) </para>
	/// <para> [2] = (a_[I0_] * b_[I1_]) - (a_[I1_] * b_[I0_]) </para>
	/// <para> [...] = default, or implied 0 if default construction is not possible. </para>
	/// <para> Unlike most EmuMath Vector functions, if no OutSize_ is provided this will always default to 3 instead of SizeA_, due to the meaning of cross products. </para>
	/// </summary>
	/// <param name="a_">: EmuMath Vector appearing as `a_` in the listed calculations.</param>
	/// <param name="b_">: EmuMath Vector appearing as `b_` in the listed calculations.</param>
	/// <returns>3D cross product of EmuMath Vectors a_ and b_, using theoretical indices I0_, I1_, I2_.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_cross_3d(const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, OutSize_, OutT_, I0_, I1_, I2_, I0_, I1_, I2_>(a_, b_);
	}

	template<typename OutT_, std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<3, OutT_> new_vector_cross_3d(const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, 3, OutT_, I0_, I1_, I2_, I0_, I1_, I2_>(a_, b_);
	}

	template<std::size_t OutSize_, std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point> new_vector_cross_3d
	(
		const EmuMath::NewVector<SizeA_, TA_>& a_,
		const EmuMath::NewVector<SizeB_, TB_>& b_
	)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, OutSize_, a_fp, I0_, I1_, I2_, I0_, I1_, I2_>(a_, b_);
	}

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, typename TA_, std::size_t SizeA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<3, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point> new_vector_cross_3d
	(
		const EmuMath::NewVector<SizeA_, TA_>& a_,
		const EmuMath::NewVector<SizeB_, TB_>& b_
	)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, 3, a_fp, I0_, I1_, I2_, I0_, I1_, I2_>(a_, b_);
	}

	/// <summary>
	/// <para> Outputs the 3D cross product of the two passed EmuMath Vectors, using theoretical indices A0_, A1_, A2_ from a_, and B0_, B1_, B2_ from b_. </para>
	/// <para> Listed output will be provided for output Vectors which contain at least up to that element: </para>
	/// <para> [0] = (a_[A1_] * b_[B2_]) - (a_[A2_] * b_[B1_]) </para>
	/// <para> [1] = (a_[A2_] * b_[B0_]) - (a_[A0_] * b_[B2_]) </para>
	/// <para> [2] = (a_[A0_] * b_[B1_]) - (a_[A1_] * b_[B0_]) </para>
	/// <para> [...] = default, or implied 0 if default construction is not possible. </para>
	/// <para> Unlike most EmuMath Vector functions, if no OutSize_ is provided this will always default to 3 instead of SizeA_, due to the meaning of cross products. </para>
	/// </summary>
	/// <param name="a_">: EmuMath Vector appearing as `a_` in the listed calculations.</param>
	/// <param name="b_">: EmuMath Vector appearing as `b_` in the listed calculations.</param>
	/// <returns>3D cross product of EmuMath Vectors a_ and b_, using theoretical indices A0_, A1_, A2_ from a_, and B0_, B1_, B2_ from b_.</returns>
	template
	<
		std::size_t OutSize_,
		typename OutT_,
		std::size_t A0_,
		std::size_t A1_,
		std::size_t A2_,
		std::size_t B0_,
		std::size_t B1_,
		std::size_t B2_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_
	>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_cross_3d(const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, OutSize_, OutT_, A0_, A1_, A2_, B0_, B1_, B2_>(a_, b_);
	}

	template
	<
		typename OutT_,
		std::size_t A0_,
		std::size_t A1_,
		std::size_t A2_,
		std::size_t B0_,
		std::size_t B1_,
		std::size_t B2_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_
	>
	[[nodiscard]] constexpr inline EmuMath::NewVector<3, OutT_> new_vector_cross_3d(const EmuMath::NewVector<SizeA_, TA_>& a_, const EmuMath::NewVector<SizeB_, TB_>& b_)
	{
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, 3, OutT_, A0_, A1_, A2_, B0_, B1_, B2_>(a_, b_);
	}

	template
	<
		std::size_t OutSize_,
		std::size_t A0_,
		std::size_t A1_,
		std::size_t A2_,
		std::size_t B0_,
		std::size_t B1_,
		std::size_t B2_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_
	>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point> new_vector_cross_3d
	(
		const EmuMath::NewVector<SizeA_, TA_>& a_,
		const EmuMath::NewVector<SizeB_, TB_>& b_
	)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, OutSize_, a_fp, A0_, A1_, A2_, B0_, B1_, B2_>(a_, b_);
	}

	template
	<
		std::size_t A0_,
		std::size_t A1_,
		std::size_t A2_,
		std::size_t B0_,
		std::size_t B1_,
		std::size_t B2_,
		typename TA_,
		std::size_t SizeA_,
		std::size_t SizeB_,
		typename TB_
	>
	[[nodiscard]] constexpr inline EmuMath::NewVector<3, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point> new_vector_cross_3d
	(
		const EmuMath::NewVector<SizeA_, TA_>& a_,
		const EmuMath::NewVector<SizeB_, TB_>& b_
	)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, 3, a_fp, A0_, A1_, A2_, B0_, B1_, B2_>(a_, b_);
	}
#pragma endregion

#pragma region SQUARE_DISTANCE_FUNCS
	/// <summary>
	/// <para> Calculates the squared distance between EmuMath Vectors from_ and to_. Equivalent to the square magnitude of (to_ - from_). </para>
	/// <para> IncludeNonContained_: If true, all contained-indices will be used for forming the distance. Otherwise, only the indices of the smallest Vector will be used. </para>
	/// </summary>
	/// <param name="from_">: EmuMath Vector to calculate the distance from.</param>
	/// <param name="to_">: EmuMath Vector to calculate the distance to.</param>
	/// <returns>Distance between the two passed EmuMath Vectors before a square root operation is performed.</returns>
	template<typename Out_, bool IncludeNonContained_ = true, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline Out_ new_vector_square_distance(const EmuMath::NewVector<FromSize_, FromT_>& from_, const EmuMath::NewVector<ToSize_, ToT_>& to_)
	{
		return _vector_underlying::_vector_square_distance<IncludeNonContained_, Out_>(from_, to_);
	}

	template<bool IncludeNonContained_ = true, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<FromSize_, FromT_>::preferred_floating_point new_vector_square_distance
	(
		const EmuMath::NewVector<FromSize_, FromT_>& from_,
		const EmuMath::NewVector<ToSize_, ToT_>& to_
	)
	{
		return _vector_underlying::_vector_square_distance<IncludeNonContained_, typename EmuMath::NewVector<FromSize_, FromT_>::preferred_floating_point>(from_, to_);
	}

	/// <summary>
	/// <para> Calculates the squared distance between EmuMath Vectors from_ and to_. Equivalent to the square magnitude of (to_ - from_). </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading from Vectors for calculating distance. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading from Vectors for calculating distance. </para>
	/// </summary>
	/// <param name="from_">: EmuMath Vector to calculate the distance from.</param>
	/// <param name="to_">: EmuMath Vector to calculate the distance to.</param>
	/// <returns>Distance between the two passed EmuMath Vectors before a square root operation is performed.</returns>
	template<typename Out_, std::size_t BeginIndex_, std::size_t EndIndex_, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline Out_ new_vector_square_distance(const EmuMath::NewVector<FromSize_, FromT_>& from_, const EmuMath::NewVector<ToSize_, ToT_>& to_)
	{
		return _vector_underlying::_vector_square_distance<BeginIndex_, EndIndex_, Out_>(from_, to_);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<FromSize_, FromT_>::preferred_floating_point new_vector_square_distance
	(
		const EmuMath::NewVector<FromSize_, FromT_>& from_,
		const EmuMath::NewVector<ToSize_, ToT_>& to_
	)
	{
		return _vector_underlying::_vector_square_distance<BeginIndex_, EndIndex_, typename EmuMath::NewVector<FromSize_, FromT_>::preferred_floating_point>(from_, to_);
	}
#pragma endregion

#pragma region DISTANCE_FUNCS
	/// <summary>
	/// <para> Calculates the distance between EmuMath Vectors from_ and to_. Equivalent to the magnitude of (to_ - from_). </para>
	/// <para> IncludeNonContained_: If true, all contained-indices will be used for forming the distance. Otherwise, only the indices of the smallest Vector will be used. </para>
	/// <para> For a guarantee to be constexpr-evaluable if possible, use vector_distance_constexpr instead. </para>
	/// </summary>
	/// <param name="from_">: EmuMath Vector to calculate the distance from.</param>
	/// <param name="to_">: EmuMath Vector to calculate the distance to.</param>
	/// <returns>Distance between the two passed EmuMath Vectors.</returns>
	template<typename Out_, bool IncludeNonContained_ = true, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline Out_ new_vector_distance(const EmuMath::NewVector<FromSize_, FromT_>& from_, const EmuMath::NewVector<ToSize_, ToT_>& to_)
	{
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt, IncludeNonContained_, Out_>(from_, to_);
	}

	template<bool IncludeNonContained_ = true, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<FromSize_, FromT_>::preferred_floating_point new_vector_distance
	(
		const EmuMath::NewVector<FromSize_, FromT_>& from_,
		const EmuMath::NewVector<ToSize_, ToT_>& to_
	)
	{
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt, IncludeNonContained_, typename EmuMath::NewVector<FromSize_, FromT_>::preferred_floating_point>(from_, to_);
	}

	/// <summary>
	/// <para> Calculates the distance between EmuMath Vectors from_ and to_. Equivalent to the magnitude of (to_ - from_). </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading from Vectors for calculating distance. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading from Vectors for calculating distance. </para>
	/// <para> For a guarantee to be constexpr-evaluable if possible, use vector_distance_constexpr instead. </para>
	/// </summary>
	/// <param name="from_">: EmuMath Vector to calculate the distance from.</param>
	/// <param name="to_">: EmuMath Vector to calculate the distance to.</param>
	/// <returns>Distance between the two passed EmuMath Vectors.</returns>
	template<typename Out_, std::size_t BeginIndex_, std::size_t EndIndex_, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline Out_ new_vector_distance(const EmuMath::NewVector<FromSize_, FromT_>& from_, const EmuMath::NewVector<ToSize_, ToT_>& to_)
	{
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt, BeginIndex_, EndIndex_, Out_>(from_, to_);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<FromSize_, FromT_>::preferred_floating_point new_vector_distance
	(
		const EmuMath::NewVector<FromSize_, FromT_>& from_,
		const EmuMath::NewVector<ToSize_, ToT_>& to_
	)
	{
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt, BeginIndex_, EndIndex_, typename EmuMath::NewVector<FromSize_, FromT_>::preferred_floating_point>(from_, to_);
	}
#pragma endregion

#pragma region DISTANCE_CONSTEXPR_FUNCS
	/// <summary>
	/// <para> Calculates the distance between EmuMath Vectors from_ and to_. Equivalent to the magnitude of (to_ - from_). </para>
	/// <para> IncludeNonContained_: If true, all contained-indices will be used for forming the distance. Otherwise, only the indices of the smallest Vector will be used. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="from_">: EmuMath Vector to calculate the distance from.</param>
	/// <param name="to_">: EmuMath Vector to calculate the distance to.</param>
	/// <returns>Distance between the two passed EmuMath Vectors.</returns>
	template<typename Out_, bool IncludeNonContained_ = true, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline Out_ new_vector_distance_constexpr(const EmuMath::NewVector<FromSize_, FromT_>& from_, const EmuMath::NewVector<ToSize_, ToT_>& to_)
	{
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt_constexpr, IncludeNonContained_, Out_>(from_, to_);
	}

	template<bool IncludeNonContained_ = true, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<FromSize_, FromT_>::preferred_floating_point new_vector_distance_constexpr
	(
		const EmuMath::NewVector<FromSize_, FromT_>& from_,
		const EmuMath::NewVector<ToSize_, ToT_>& to_
	)
	{
		using from_fp = typename EmuMath::NewVector<FromSize_, FromT_>::preferred_floating_point;
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt_constexpr, IncludeNonContained_, from_fp>(from_, to_);
	}

	/// <summary>
	/// <para> Calculates the distance between EmuMath Vectors from_ and to_. Equivalent to the magnitude of (to_ - from_). </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading from Vectors for calculating distance. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading from Vectors for calculating distance. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="from_">: EmuMath Vector to calculate the distance from.</param>
	/// <param name="to_">: EmuMath Vector to calculate the distance to.</param>
	/// <returns>Distance between the two passed EmuMath Vectors.</returns>
	template<typename Out_, std::size_t BeginIndex_, std::size_t EndIndex_, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline Out_ new_vector_distance_constexpr(const EmuMath::NewVector<FromSize_, FromT_>& from_, const EmuMath::NewVector<ToSize_, ToT_>& to_)
	{
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, Out_>(from_, to_);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<FromSize_, FromT_>::preferred_floating_point new_vector_distance_constexpr
	(
		const EmuMath::NewVector<FromSize_, FromT_>& from_,
		const EmuMath::NewVector<ToSize_, ToT_>& to_
	)
	{
		using from_fp = typename EmuMath::NewVector<FromSize_, FromT_>::preferred_floating_point;
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, from_fp>(from_, to_);
	}
#pragma endregion
}

#endif
