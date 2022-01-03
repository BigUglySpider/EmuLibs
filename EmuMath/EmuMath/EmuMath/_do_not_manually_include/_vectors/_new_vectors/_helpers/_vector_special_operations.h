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
}

#endif
