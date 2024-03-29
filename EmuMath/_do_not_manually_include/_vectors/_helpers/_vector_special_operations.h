#ifndef EMU_MATH_VECTOR_SPECIAL_OPERATIONS_H_INC_
#define EMU_MATH_VECTOR_SPECIAL_OPERATIONS_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../EmuCore/Functors/Arithmetic.h"

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
// --- reflect_normal
// --- normal_to_plane_3d_no_norm
// --- normal_to_plane_3d_constexpr
// --- normal_to_plane_3d
// --- project
// --- project_plane
// --- project_plane_3d_constexpr
// --- project_plane_3d

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
	[[nodiscard]] constexpr inline Out_ vector_dot(const EmuMath::Vector<SizeA_, TA_>& vector_a_, const EmuMath::Vector<SizeB_, TB_>& vector_b_)
	{
		return _vector_underlying::_vector_dot<Out_>(vector_a_, vector_b_);
	}
	template<std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point vector_dot
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		return _vector_underlying::_vector_dot<typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point>(vector_a_, vector_b_);
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
	[[nodiscard]] constexpr inline Out_ vector_dot(const EmuMath::Vector<SizeA_, TA_>& vector_a_, const EmuMath::Vector<SizeB_, TB_>& vector_b_)
	{
		return _vector_underlying::_vector_dot<BeginIndex_, EndIndex_, Out_>(vector_a_, vector_b_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point vector_dot
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		return _vector_underlying::_vector_dot<BeginIndex_, EndIndex_, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point>(vector_a_, vector_b_);
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
	[[nodiscard]] constexpr inline Out_ vector_square_magnitude(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_square_mag<Out_>(vector_);
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::preferred_floating_point vector_square_magnitude(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_square_mag<typename EmuMath::Vector<Size_, T_>::preferred_floating_point>(vector_);
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
	[[nodiscard]] constexpr inline Out_ vector_square_magnitude(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_square_mag<BeginIndex_, EndIndex_, Out_>(vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::preferred_floating_point vector_square_magnitude(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_square_mag<BeginIndex_, EndIndex_, typename EmuMath::Vector<Size_, T_>::preferred_floating_point>(vector_);
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
	[[nodiscard]] constexpr inline Out_ vector_magnitude_constexpr(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt_constexpr, Out_>(vector_);
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::preferred_floating_point vector_magnitude_constexpr(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt_constexpr, typename EmuMath::Vector<Size_, T_>::preferred_floating_point>(vector_);
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
	[[nodiscard]] constexpr inline Out_ vector_magnitude_constexpr(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, Out_>(vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::preferred_floating_point vector_magnitude_constexpr(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, typename EmuMath::Vector<Size_, T_>::preferred_floating_point>(vector_);
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
	[[nodiscard]] constexpr inline Out_ vector_magnitude(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt, Out_>(vector_);
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::preferred_floating_point vector_magnitude(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt, typename EmuMath::Vector<Size_, T_>::preferred_floating_point>(vector_);
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
	[[nodiscard]] constexpr inline Out_ vector_magnitude(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt, BeginIndex_, EndIndex_, Out_>(vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::preferred_floating_point vector_magnitude(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt, BeginIndex_, EndIndex_, typename EmuMath::Vector<Size_, T_>::preferred_floating_point>(vector_);
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
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_normalise_constexpr(const EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, OutSize_, OutT_>(in_vector_);
	}
	template<typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, OutT_> vector_normalise_constexpr(const EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, InSize_, OutT_>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point> vector_normalise_constexpr
	(
		const EmuMath::Vector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, OutSize_, out_arg>(in_vector_);
	}
	template<typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point> vector_normalise_constexpr
	(
		const EmuMath::Vector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point;
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
	constexpr inline void vector_normalise_constexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<InSize_, InT_>& in_vector_)
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
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_normalise_range_constexpr(const EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, OutSize_, OutT_>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, OutT_> vector_normalise_range_constexpr(const EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, InSize_, OutT_>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point> vector_normalise_range_constexpr
	(
		const EmuMath::Vector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, OutSize_, out_arg>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point> vector_normalise_range_constexpr
	(
		const EmuMath::Vector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point;
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
	constexpr inline void vector_normalise_range_constexpr(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<InSize_, InT_>& in_vector_)
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
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_normalise(const EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, OutSize_, OutT_>(in_vector_);
	}
	template<typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, OutT_> vector_normalise(const EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, InSize_, OutT_>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point> vector_normalise
	(
		const EmuMath::Vector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, OutSize_, out_arg>(in_vector_);
	}
	template<typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point> vector_normalise
	(
		const EmuMath::Vector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, InSize_, out_arg>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a normalised form of the provided in_vector_, via the provided out_vector_. </para>
	/// <para> For a guarantee to produce a compile-time result if possible, use `vector_normalise_constexpr` instead. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="in_vector_">: EmuMath Vector to calculate the normalised form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void vector_normalise(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<InSize_, InT_>& in_vector_)
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
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_normalise_range(const EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, BeginIndex_, EndIndex_, OutSize_, OutT_>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, OutT_> vector_normalise_range(const EmuMath::Vector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, BeginIndex_, EndIndex_, InSize_, OutT_>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point> vector_normalise_range
	(
		const EmuMath::Vector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point;
		return _vector_underlying::_vector_normalise<EmuCore::do_sqrt, BeginIndex_, EndIndex_, OutSize_, out_arg>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<InSize_, typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point> vector_normalise_range
	(
		const EmuMath::Vector<InSize_, InT_>& in_vector_
	)
	{
		using out_arg = typename EmuMath::Vector<InSize_, InT_>::preferred_floating_point;
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
	constexpr inline void vector_normalise_range(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<InSize_, InT_>& in_vector_)
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
	[[nodiscard]] constexpr inline Out_ vector_angle_cos_constexpr(const EmuMath::Vector<SizeA_, TA_>& vector_a_, const EmuMath::Vector<SizeB_, TB_>& vector_b_)
	{
		return _vector_underlying::_vector_angle_cos<EmuCore::do_sqrt_constexpr, Out_, Radians_>(vector_a_, vector_b_);
	}
	template<bool Radians_ = true, typename TA_, std::size_t SizeA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point vector_angle_cos_constexpr
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		using out_type_arg = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
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
	[[nodiscard]] constexpr inline Out_ vector_angle_cos(const EmuMath::Vector<SizeA_, TA_>& vector_a_, const EmuMath::Vector<SizeB_, TB_>& vector_b_)
	{
		return _vector_underlying::_vector_angle_cos<EmuCore::do_sqrt, Out_, Radians_>(vector_a_, vector_b_);
	}
	template<bool Radians_ = true, typename TA_, std::size_t SizeA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point vector_angle_cos
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		using out_type_arg = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
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
	[[nodiscard]] constexpr inline Out_ vector_angle(const EmuMath::Vector<SizeA_, TA_>& vector_a_, const EmuMath::Vector<SizeB_, TB_>& vector_b_)
	{
		return _vector_underlying::_vector_angle<EmuCore::do_sqrt, EmuCore::do_acos, Out_, Radians_>(vector_a_, vector_b_);
	}
	template<bool Radians_ = true, typename TA_, std::size_t SizeA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point vector_angle
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		using out_type_arg = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
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
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_cross_3d(const EmuMath::Vector<SizeA_, TA_>& a_, const EmuMath::Vector<SizeB_, TB_>& b_)
	{
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, OutSize_, OutT_, 0, 1, 2, 0, 1, 2>(a_, b_);
	}

	template<typename OutT_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> vector_cross_3d(const EmuMath::Vector<SizeA_, TA_>& a_, const EmuMath::Vector<SizeB_, TB_>& b_)
	{
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, 3, OutT_, 0, 1, 2, 0, 1, 2>(a_, b_);
	}

	template<std::size_t OutSize_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_cross_3d
	(
		const EmuMath::Vector<SizeA_, TA_>& a_,
		const EmuMath::Vector<SizeB_, TB_>& b_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, OutSize_, a_fp, 0, 1, 2, 0, 1, 2>(a_, b_);
	}

	template<typename TA_, std::size_t SizeA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_cross_3d
	(
		const EmuMath::Vector<SizeA_, TA_>& a_,
		const EmuMath::Vector<SizeB_, TB_>& b_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
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
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_cross_3d(const EmuMath::Vector<SizeA_, TA_>& a_, const EmuMath::Vector<SizeB_, TB_>& b_)
	{
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, OutSize_, OutT_, I0_, I1_, I2_, I0_, I1_, I2_>(a_, b_);
	}

	template<typename OutT_, std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> vector_cross_3d(const EmuMath::Vector<SizeA_, TA_>& a_, const EmuMath::Vector<SizeB_, TB_>& b_)
	{
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, 3, OutT_, I0_, I1_, I2_, I0_, I1_, I2_>(a_, b_);
	}

	template<std::size_t OutSize_, std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_cross_3d
	(
		const EmuMath::Vector<SizeA_, TA_>& a_,
		const EmuMath::Vector<SizeB_, TB_>& b_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_cross_3d<EmuCore::do_multiply, EmuCore::do_subtract, OutSize_, a_fp, I0_, I1_, I2_, I0_, I1_, I2_>(a_, b_);
	}

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, typename TA_, std::size_t SizeA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_cross_3d
	(
		const EmuMath::Vector<SizeA_, TA_>& a_,
		const EmuMath::Vector<SizeB_, TB_>& b_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
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
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_cross_3d(const EmuMath::Vector<SizeA_, TA_>& a_, const EmuMath::Vector<SizeB_, TB_>& b_)
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
	[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> vector_cross_3d(const EmuMath::Vector<SizeA_, TA_>& a_, const EmuMath::Vector<SizeB_, TB_>& b_)
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
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_cross_3d
	(
		const EmuMath::Vector<SizeA_, TA_>& a_,
		const EmuMath::Vector<SizeB_, TB_>& b_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
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
	[[nodiscard]] constexpr inline EmuMath::Vector<3, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_cross_3d
	(
		const EmuMath::Vector<SizeA_, TA_>& a_,
		const EmuMath::Vector<SizeB_, TB_>& b_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
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
	[[nodiscard]] constexpr inline Out_ vector_square_distance(const EmuMath::Vector<FromSize_, FromT_>& from_, const EmuMath::Vector<ToSize_, ToT_>& to_)
	{
		return _vector_underlying::_vector_square_distance<IncludeNonContained_, Out_>(from_, to_);
	}

	template<bool IncludeNonContained_ = true, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point vector_square_distance
	(
		const EmuMath::Vector<FromSize_, FromT_>& from_,
		const EmuMath::Vector<ToSize_, ToT_>& to_
	)
	{
		return _vector_underlying::_vector_square_distance<IncludeNonContained_, typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point>(from_, to_);
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
	[[nodiscard]] constexpr inline Out_ vector_square_distance(const EmuMath::Vector<FromSize_, FromT_>& from_, const EmuMath::Vector<ToSize_, ToT_>& to_)
	{
		return _vector_underlying::_vector_square_distance<BeginIndex_, EndIndex_, Out_>(from_, to_);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point vector_square_distance
	(
		const EmuMath::Vector<FromSize_, FromT_>& from_,
		const EmuMath::Vector<ToSize_, ToT_>& to_
	)
	{
		return _vector_underlying::_vector_square_distance<BeginIndex_, EndIndex_, typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point>(from_, to_);
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
	[[nodiscard]] constexpr inline Out_ vector_distance(const EmuMath::Vector<FromSize_, FromT_>& from_, const EmuMath::Vector<ToSize_, ToT_>& to_)
	{
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt, IncludeNonContained_, Out_>(from_, to_);
	}

	template<bool IncludeNonContained_ = true, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point vector_distance
	(
		const EmuMath::Vector<FromSize_, FromT_>& from_,
		const EmuMath::Vector<ToSize_, ToT_>& to_
	)
	{
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt, IncludeNonContained_, typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point>(from_, to_);
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
	[[nodiscard]] constexpr inline Out_ vector_distance(const EmuMath::Vector<FromSize_, FromT_>& from_, const EmuMath::Vector<ToSize_, ToT_>& to_)
	{
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt, BeginIndex_, EndIndex_, Out_>(from_, to_);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point vector_distance
	(
		const EmuMath::Vector<FromSize_, FromT_>& from_,
		const EmuMath::Vector<ToSize_, ToT_>& to_
	)
	{
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt, BeginIndex_, EndIndex_, typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point>(from_, to_);
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
	[[nodiscard]] constexpr inline Out_ vector_distance_constexpr(const EmuMath::Vector<FromSize_, FromT_>& from_, const EmuMath::Vector<ToSize_, ToT_>& to_)
	{
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt_constexpr, IncludeNonContained_, Out_>(from_, to_);
	}

	template<bool IncludeNonContained_ = true, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point vector_distance_constexpr
	(
		const EmuMath::Vector<FromSize_, FromT_>& from_,
		const EmuMath::Vector<ToSize_, ToT_>& to_
	)
	{
		using from_fp = typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point;
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
	[[nodiscard]] constexpr inline Out_ vector_distance_constexpr(const EmuMath::Vector<FromSize_, FromT_>& from_, const EmuMath::Vector<ToSize_, ToT_>& to_)
	{
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, Out_>(from_, to_);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename FromT_, std::size_t FromSize_, typename ToT_, std::size_t ToSize_>
	[[nodiscard]] constexpr inline typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point vector_distance_constexpr
	(
		const EmuMath::Vector<FromSize_, FromT_>& from_,
		const EmuMath::Vector<ToSize_, ToT_>& to_
	)
	{
		using from_fp = typename EmuMath::Vector<FromSize_, FromT_>::preferred_floating_point;
		return _vector_underlying::_vector_distance<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, from_fp>(from_, to_);
	}
#pragma endregion

#pragma region REFLECT_NORMAL_FUNCS
	/// <summary>
	/// <para> Calculates a reflection Vector using the provided ray_ (direction) Vector and normal_ Vector. </para>
	/// </summary>
	/// <param name="ray_">: Vector to be reflected.</param>
	/// <param name="normal_">: Normal describing a reflection surface. This is expected to be normalised, and treated as such.</param>
	/// <returns>EmuMath Vector representing the reflection of the provided ray_ on the provided surface normal_.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t RaySize_, typename RayT_, std::size_t NormalSize_, typename NormalT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_reflect_normal
	(
		const EmuMath::Vector<RaySize_, RayT_>& ray_,
		const EmuMath::Vector<NormalSize_, NormalT_>& normal_
	)
	{
		return _vector_underlying::_vector_reflect_normal<EmuCore::do_subtract, EmuCore::do_multiply, OutSize_, OutT_>(ray_, normal_);
	}

	template<typename OutT_, std::size_t RaySize_, typename RayT_, std::size_t NormalSize_, typename NormalT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<RaySize_, OutT_> vector_reflect_normal
	(
		const EmuMath::Vector<RaySize_, RayT_>& ray_,
		const EmuMath::Vector<NormalSize_, NormalT_>& normal_
	)
	{
		return _vector_underlying::_vector_reflect_normal<EmuCore::do_subtract, EmuCore::do_multiply, RaySize_, OutT_>(ray_, normal_);
	}

	template<std::size_t OutSize_, std::size_t RaySize_, typename RayT_, std::size_t NormalSize_, typename NormalT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<RaySize_, RayT_>::preferred_floating_point> vector_reflect_normal
	(
		const EmuMath::Vector<RaySize_, RayT_>& ray_,
		const EmuMath::Vector<NormalSize_, NormalT_>& normal_
	)
	{
		using ray_fp = typename EmuMath::Vector<RaySize_, RayT_>::preferred_floating_point;
		return _vector_underlying::_vector_reflect_normal<EmuCore::do_subtract, EmuCore::do_multiply, OutSize_, ray_fp>(ray_, normal_);
	}

	template<typename RayT_, typename NormalT_, std::size_t RaySize_, std::size_t NormalSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<RaySize_, typename EmuMath::Vector<RaySize_, RayT_>::preferred_floating_point> vector_reflect_normal
	(
		const EmuMath::Vector<RaySize_, RayT_>& ray_,
		const EmuMath::Vector<NormalSize_, NormalT_>& normal_
	)
	{
		using ray_fp = typename EmuMath::Vector<RaySize_, RayT_>::preferred_floating_point;
		return _vector_underlying::_vector_reflect_normal<EmuCore::do_subtract, EmuCore::do_multiply, RaySize_, ray_fp>(ray_, normal_);
	}

	/// <summary>
	/// <para> Calculates a reflection Vector using the provided ray_ (direction) Vector and normal_ Vector, using indices within the provided range. </para>
	/// <para>
	///		Calculations will be performed as though the indices within the provided range form a Vector of that size. 
	///		For example, if using 3 indices within a Vector of 8 indices, the reflection will be performed as though on a 3-element Vector.
	/// </para>
	/// <para> BeginIndex_: Inclusive index at which to start performing reflection calculations. </para>
	/// <para> EndIndex_: Exclusive index at which to stop performing reflection calculations. </para>
	/// </summary>
	/// <param name="ray_">: Vector to be reflected.</param>
	/// <param name="normal_">: Normal describing a reflection surface. This is expected to be normalised, and treated as such.</param>
	/// <returns>EmuMath Vector representing the reflection of the provided ray_ on the provided surface normal_, using indices within the provided range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t RaySize_, typename RayT_, std::size_t NormalSize_, typename NormalT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_reflect_normal
	(
		const EmuMath::Vector<RaySize_, RayT_>& ray_,
		const EmuMath::Vector<NormalSize_, NormalT_>& normal_
	)
	{
		return _vector_underlying::_vector_reflect_normal<EmuCore::do_subtract, EmuCore::do_multiply, BeginIndex_, EndIndex_, OutSize_, OutT_>(ray_, normal_);
	}

	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t RaySize_, typename RayT_, std::size_t NormalSize_, typename NormalT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<RaySize_, OutT_> vector_reflect_normal
	(
		const EmuMath::Vector<RaySize_, RayT_>& ray_,
		const EmuMath::Vector<NormalSize_, NormalT_>& normal_
	)
	{
		return _vector_underlying::_vector_reflect_normal<EmuCore::do_subtract, EmuCore::do_multiply, BeginIndex_, EndIndex_, RaySize_, OutT_>(ray_, normal_);
	}

	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t RaySize_, typename RayT_, std::size_t NormalSize_, typename NormalT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<RaySize_, RayT_>::preferred_floating_point> vector_reflect_normal
	(
		const EmuMath::Vector<RaySize_, RayT_>& ray_,
		const EmuMath::Vector<NormalSize_, NormalT_>& normal_
	)
	{
		using ray_fp = typename EmuMath::Vector<RaySize_, RayT_>::preferred_floating_point;
		return _vector_underlying::_vector_reflect_normal<EmuCore::do_subtract, EmuCore::do_multiply, BeginIndex_, EndIndex_, OutSize_, ray_fp>(ray_, normal_);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename RayT_, std::size_t RaySize_, typename NormalT_, std::size_t NormalSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<RaySize_, typename EmuMath::Vector<RaySize_, RayT_>::preferred_floating_point> vector_reflect_normal
	(
		const EmuMath::Vector<RaySize_, RayT_>& ray_,
		const EmuMath::Vector<NormalSize_, NormalT_>& normal_
	)
	{
		using ray_fp = typename EmuMath::Vector<RaySize_, RayT_>::preferred_floating_point;
		return _vector_underlying::_vector_reflect_normal<EmuCore::do_subtract, EmuCore::do_multiply, BeginIndex_, EndIndex_, RaySize_, ray_fp>(ray_, normal_);
	}
#pragma endregion

#pragma region NORMAL_TO_PLANE_3D_NO_NORM_FUNCS
	/// <summary>
	/// <para> Calculates the Vector normal to a plane defined by 3 points in 3D space, before normalisation. </para>
	/// <para> The result may be summarised as Cross(point_b_ - point_a_, point_c_ - point_a_). </para>
	/// <para> ReadOffset_: Optional inclusive index offset at which to start reading Vectors. Defaults to 0. </para>
	/// <para> Unlike most EmuMath Vector functions, if no OutSize_ is provided this will always default to 3 instead of SizeA_, due to its 3D focus. </para>
	/// </summary>
	/// <param name="point_a_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_a_` in described calculations.</param>
	/// <param name="point_b_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_b_` in described calculations.</param>
	/// <param name="point_c_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_c_` in described calculations.</param>
	/// <returns>EmuMath Vector normal to the plane defined by the passed 3 coordinates, before normalisation.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t ReadOffset_ = 0, typename TA_, std::size_t SizeA_, typename TB_, std::size_t SizeB_, typename TC_, std::size_t SizeC_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_normal_to_plane_3d_no_norm
	(
		const EmuMath::Vector<SizeA_, TA_>& point_a_,
		const EmuMath::Vector<SizeB_, TB_>& point_b_,
		const EmuMath::Vector<SizeC_, TC_>& point_c_
	)
	{
		return _vector_underlying::_vector_normal_to_plane_3d_no_norm<EmuCore::do_multiply, EmuCore::do_subtract, OutSize_, OutT_, ReadOffset_>(point_a_, point_b_, point_c_);
	}

	template<typename OutT_, std::size_t ReadOffset_ = 0, typename TA_, std::size_t SizeA_, typename TB_, std::size_t SizeB_, typename TC_, std::size_t SizeC_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> vector_normal_to_plane_3d_no_norm
	(
		const EmuMath::Vector<SizeA_, TA_>& point_a_,
		const EmuMath::Vector<SizeB_, TB_>& point_b_,
		const EmuMath::Vector<SizeC_, TC_>& point_c_
	)
	{
		return _vector_underlying::_vector_normal_to_plane_3d_no_norm<EmuCore::do_multiply, EmuCore::do_subtract, 3, OutT_, ReadOffset_>(point_a_, point_b_, point_c_);
	}

	template<std::size_t OutSize_, std::size_t ReadOffset_ = 0, typename TA_, std::size_t SizeA_, typename TB_, std::size_t SizeB_, typename TC_, std::size_t SizeC_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_normal_to_plane_3d_no_norm
	(
		const EmuMath::Vector<SizeA_, TA_>& point_a_,
		const EmuMath::Vector<SizeB_, TB_>& point_b_,
		const EmuMath::Vector<SizeC_, TC_>& point_c_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_normal_to_plane_3d_no_norm<EmuCore::do_multiply, EmuCore::do_subtract, OutSize_, a_fp, ReadOffset_>(point_a_, point_b_, point_c_);
	}

	template<typename TA_, typename TB_, typename TC_, std::size_t SizeA_, std::size_t SizeB_, std::size_t SizeC_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_normal_to_plane_3d_no_norm
	(
		const EmuMath::Vector<SizeA_, TA_>& point_a_,
		const EmuMath::Vector<SizeB_, TB_>& point_b_,
		const EmuMath::Vector<SizeC_, TC_>& point_c_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_normal_to_plane_3d_no_norm<EmuCore::do_multiply, EmuCore::do_subtract, 3, a_fp, 0>(point_a_, point_b_, point_c_);
	}
#pragma endregion

#pragma region NORMAL_TO_PLANE_3D_CONSTEXPR_FUNCS
	/// <summary>
	/// <para> Calculates the Vector normal to a plane defined by 3 points in 3D space. </para>
	/// <para> The result may be summarised as Normalise(Cross(point_b_ - point_a_, point_c_ - point_a_)). </para>
	/// <para> ReadOffset_: Optional inclusive index offset at which to start reading Vectors. Defaults to 0. </para>
	/// <para> Unlike most EmuMath Vector functions, if no OutSize_ is provided this will always default to 3 instead of SizeA_, due to its 3D focus. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="point_a_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_a_` in described calculations.</param>
	/// <param name="point_b_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_b_` in described calculations.</param>
	/// <param name="point_c_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_c_` in described calculations.</param>
	/// <returns>EmuMath Vector normal to the plane defined by the passed 3 coordinates.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t ReadOffset_ = 0, typename TA_, std::size_t SizeA_, typename TB_, std::size_t SizeB_, typename TC_, std::size_t SizeC_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_normal_to_plane_3d_constexpr
	(
		const EmuMath::Vector<SizeA_, TA_>& point_a_,
		const EmuMath::Vector<SizeB_, TB_>& point_b_,
		const EmuMath::Vector<SizeC_, TC_>& point_c_
	)
	{
		return _vector_underlying::_vector_normal_to_plane_3d<EmuCore::do_multiply, EmuCore::do_subtract, EmuCore::do_sqrt_constexpr, OutSize_, OutT_, ReadOffset_>
		(
			point_a_,
			point_b_,
			point_c_
		);
	}

	template<typename OutT_, std::size_t ReadOffset_ = 0, typename TA_, std::size_t SizeA_, typename TB_, std::size_t SizeB_, typename TC_, std::size_t SizeC_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> vector_normal_to_plane_3d_constexpr
	(
		const EmuMath::Vector<SizeA_, TA_>& point_a_,
		const EmuMath::Vector<SizeB_, TB_>& point_b_,
		const EmuMath::Vector<SizeC_, TC_>& point_c_
	)
	{
		return _vector_underlying::_vector_normal_to_plane_3d<EmuCore::do_multiply, EmuCore::do_subtract, EmuCore::do_sqrt_constexpr, 3, OutT_, ReadOffset_>
		(
			point_a_,
			point_b_,
			point_c_
		);
	}

	template<std::size_t OutSize_, std::size_t ReadOffset_ = 0, typename TA_, std::size_t SizeA_, typename TB_, std::size_t SizeB_, typename TC_, std::size_t SizeC_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_normal_to_plane_3d_constexpr
	(
		const EmuMath::Vector<SizeA_, TA_>& point_a_,
		const EmuMath::Vector<SizeB_, TB_>& point_b_,
		const EmuMath::Vector<SizeC_, TC_>& point_c_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_normal_to_plane_3d<EmuCore::do_multiply, EmuCore::do_subtract, EmuCore::do_sqrt_constexpr, OutSize_, a_fp, ReadOffset_>
		(
			point_a_,
			point_b_,
			point_c_
		);
	}

	template<typename TA_, typename TB_, typename TC_, std::size_t SizeA_, std::size_t SizeB_, std::size_t SizeC_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_normal_to_plane_3d_constexpr
	(
		const EmuMath::Vector<SizeA_, TA_>& point_a_,
		const EmuMath::Vector<SizeB_, TB_>& point_b_,
		const EmuMath::Vector<SizeC_, TC_>& point_c_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_normal_to_plane_3d<EmuCore::do_multiply, EmuCore::do_subtract, EmuCore::do_sqrt_constexpr, 3, a_fp, 0>
		(
			point_a_,
			point_b_,
			point_c_
		);
	}
#pragma endregion

#pragma region NORMAL_TO_PLANE_3D_FUNCS
	/// <summary>
	/// <para> Calculates the Vector normal to a plane defined by 3 points in 3D space. </para>
	/// <para> The result may be summarised as Normalise(Cross(point_b_ - point_a_, point_c_ - point_a_)). </para>
	/// <para> ReadOffset_: Optional inclusive index offset at which to start reading Vectors. Defaults to 0. </para>
	/// <para> Unlike most EmuMath Vector functions, if no OutSize_ is provided this will always default to 3 instead of SizeA_, due to its 3D focus. </para>
	/// <para> For a guarantee to be constexpr-evaluable if possible, use vector_normal_to_plane_3d_constexpr instead. </para>
	/// </summary>
	/// <param name="point_a_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_a_` in described calculations.</param>
	/// <param name="point_b_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_b_` in described calculations.</param>
	/// <param name="point_c_">EmuMath Vector to interpret as a 3D cartesian coordinate, appearing as `point_c_` in described calculations.</param>
	/// <returns>EmuMath Vector normal to the plane defined by the passed 3 coordinates.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t ReadOffset_ = 0, typename TA_, std::size_t SizeA_, typename TB_, std::size_t SizeB_, typename TC_, std::size_t SizeC_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_normal_to_plane_3d
	(
		const EmuMath::Vector<SizeA_, TA_>& point_a_,
		const EmuMath::Vector<SizeB_, TB_>& point_b_,
		const EmuMath::Vector<SizeC_, TC_>& point_c_
	)
	{
		return _vector_underlying::_vector_normal_to_plane_3d<EmuCore::do_multiply, EmuCore::do_subtract, EmuCore::do_sqrt, OutSize_, OutT_, ReadOffset_>
		(
			point_a_,
			point_b_,
			point_c_
		);
	}

	template<typename OutT_, std::size_t ReadOffset_ = 0, typename TA_, std::size_t SizeA_, typename TB_, std::size_t SizeB_, typename TC_, std::size_t SizeC_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> vector_normal_to_plane_3d
	(
		const EmuMath::Vector<SizeA_, TA_>& point_a_,
		const EmuMath::Vector<SizeB_, TB_>& point_b_,
		const EmuMath::Vector<SizeC_, TC_>& point_c_
	)
	{
		return _vector_underlying::_vector_normal_to_plane_3d<EmuCore::do_multiply, EmuCore::do_subtract, EmuCore::do_sqrt, 3, OutT_, ReadOffset_>
		(
			point_a_,
			point_b_,
			point_c_
		);
	}

	template<std::size_t OutSize_, std::size_t ReadOffset_ = 0, typename TA_, std::size_t SizeA_, typename TB_, std::size_t SizeB_, typename TC_, std::size_t SizeC_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_normal_to_plane_3d
	(
		const EmuMath::Vector<SizeA_, TA_>& point_a_,
		const EmuMath::Vector<SizeB_, TB_>& point_b_,
		const EmuMath::Vector<SizeC_, TC_>& point_c_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_normal_to_plane_3d<EmuCore::do_multiply, EmuCore::do_subtract, EmuCore::do_sqrt, OutSize_, a_fp, ReadOffset_>
		(
			point_a_,
			point_b_,
			point_c_
		);
	}

	template<typename TA_, typename TB_, typename TC_, std::size_t SizeA_, std::size_t SizeB_, std::size_t SizeC_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_normal_to_plane_3d
	(
		const EmuMath::Vector<SizeA_, TA_>& point_a_,
		const EmuMath::Vector<SizeB_, TB_>& point_b_,
		const EmuMath::Vector<SizeC_, TC_>& point_c_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_normal_to_plane_3d<EmuCore::do_multiply, EmuCore::do_subtract, EmuCore::do_sqrt, 3, a_fp, 0>
		(
			point_a_,
			point_b_,
			point_c_
		);
	}
#pragma endregion

#pragma region PROJECT_FUNCS
	/// <summary>
	/// <para> Calculates the Vector resulting from projecting vector_a_ onto vector_b_. </para>
	/// </summary>
	/// <param name="vector_a_">EmuMath Vector to project via.</param>
	/// <param name="vector_b_">EmuMath Vector to project onto.</param>
	/// <returns>EmuMath Vector resulting from a projection of vector_a_ onto vector_b_.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_project
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		return _vector_underlying::_vector_project<EmuCore::do_multiply, EmuCore::do_reciprocal, OutSize_, OutT_>(vector_a_, vector_b_);
	}

	template<typename OutT_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeA_, OutT_> vector_project
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		return _vector_underlying::_vector_project<EmuCore::do_multiply, EmuCore::do_reciprocal, SizeA_, OutT_>(vector_a_, vector_b_);
	}

	template<std::size_t OutSize_, std::size_t SizeA_, typename TA_, typename TB_, std::size_t SizeB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_project
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preffered_floating_point;
		return _vector_underlying::_vector_project<EmuCore::do_multiply, EmuCore::do_reciprocal, OutSize_, a_fp>(vector_a_, vector_b_);
	}

	template<typename TA_, typename TB_, std::size_t SizeA_, std::size_t SizeB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeA_, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_project
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_project<EmuCore::do_multiply, EmuCore::do_reciprocal, SizeA_, a_fp>(vector_a_, vector_b_);
	}

	/// <summary>
	/// <para> Calculates the Vector resulting from projecting vector_a_ onto vector_b_, using indices within the specified range. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading/writing from/to Vectors. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading/writing from/to Vectors. </para>
	/// </summary>
	/// <param name="vector_a_">EmuMath Vector to project via.</param>
	/// <param name="vector_b_">EmuMath Vector to project onto.</param>
	/// <returns>EmuMath Vector resulting from a projection of vector_a_ onto vector_b_, using indices within the specified range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_project
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		return _vector_underlying::_vector_project<EmuCore::do_multiply, EmuCore::do_reciprocal, OutSize_, OutT_, BeginIndex_, EndIndex_>(vector_a_, vector_b_);
	}

	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeA_, OutT_> vector_project
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		return _vector_underlying::_vector_project<EmuCore::do_multiply, EmuCore::do_reciprocal, SizeA_, OutT_, BeginIndex_, EndIndex_>(vector_a_, vector_b_);
	}

	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, typename TA_, std::size_t SizeA_, typename TB_, std::size_t SizeB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_project
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preffered_floating_point;
		return _vector_underlying::_vector_project<EmuCore::do_multiply, EmuCore::do_reciprocal, OutSize_, a_fp, BeginIndex_, EndIndex_>(vector_a_, vector_b_);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename TA_, typename TB_, std::size_t SizeA_, std::size_t SizeB_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeA_, typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point> vector_project
	(
		const EmuMath::Vector<SizeA_, TA_>& vector_a_,
		const EmuMath::Vector<SizeB_, TB_>& vector_b_
	)
	{
		using a_fp = typename EmuMath::Vector<SizeA_, TA_>::preferred_floating_point;
		return _vector_underlying::_vector_project<EmuCore::do_multiply, EmuCore::do_reciprocal, SizeA_, a_fp, BeginIndex_, EndIndex_>(vector_a_, vector_b_);
	}
#pragma endregion

#pragma region PROJECT_PLANE_FUNCS
	/// <summary>
	/// <para> Calculates the projection of the passed Vector to_project_ onto the plane defined by the passed plane_normal_. </para>
	/// </summary>
	/// <param name="to_project_">: EmuMath Vector to project onto the target plane.</param>
	/// <param name="plane_normal_">: EmuMath Vector describing the plane to reflect onto. This is expected to be normalised, and treated as such.</param>
	/// <returns>EmuMath Vector resulting from projecting the Vector to_project_ onto the plane defined by the provided plane_normal_.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t ProjSize_, typename ProjT_, std::size_t NormSize_, typename NormT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_project_plane
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<NormSize_, NormT_>& plane_normal_
	)
	{
		return _vector_underlying::_vector_project_plane<EmuCore::do_subtract, EmuCore::do_multiply, EmuCore::do_reciprocal, OutSize_, OutT_>
		(
			to_project_,
			plane_normal_
		);
	}

	template<typename OutT_, std::size_t ProjSize_, typename ProjT_, std::size_t NormSize_, typename NormT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<ProjSize_, OutT_> vector_project_plane
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<NormSize_, NormT_>& plane_normal_
	)
	{
		return _vector_underlying::_vector_project_plane<EmuCore::do_subtract, EmuCore::do_multiply, EmuCore::do_reciprocal, ProjSize_, OutT_>
		(
			to_project_,
			plane_normal_
		);
	}

	template<std::size_t OutSize_, std::size_t ProjSize_, typename ProjT_, std::size_t NormSize_, typename NormT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point> vector_project_plane
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<NormSize_, NormT_>& plane_normal_
	)
	{
		using proj_fp = typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point;
		return _vector_underlying::_vector_project_plane<EmuCore::do_subtract, EmuCore::do_multiply, EmuCore::do_reciprocal, OutSize_, proj_fp>
		(
			to_project_,
			plane_normal_
		);
	}

	template<typename ProjT_, typename NormT_, std::size_t ProjSize_, std::size_t NormSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<ProjSize_, typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point> vector_project_plane
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<NormSize_, NormT_>& plane_normal_
	)
	{
		using proj_fp = typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point;
		return _vector_underlying::_vector_project_plane<EmuCore::do_subtract, EmuCore::do_multiply, EmuCore::do_reciprocal, ProjSize_, proj_fp>
		(
			to_project_,
			plane_normal_
		);
	}

	/// <summary>
	/// <para> Calculates the projection of the passed Vector to_project_ onto the plane defined by the passed plane_normal_, using indices in the provided range. </para>
	/// </summary>
	/// <param name="to_project_">: EmuMath Vector to project onto the target plane.</param>
	/// <param name="plane_normal_">: EmuMath Vector describing the plane to reflect onto. This is expected to be normalised, and treated as such.</param>
	/// <returns>EmuMath Vector resulting from projecting the Vector to_project_ onto the plane defined by the provided plane_normal_, using indices in the provided range..</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ProjSize_, typename ProjT_, std::size_t NormSize_, typename NormT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_project_plane
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<NormSize_, NormT_>& plane_normal_
	)
	{
		return _vector_underlying::_vector_project_plane<EmuCore::do_subtract, EmuCore::do_multiply, EmuCore::do_reciprocal, OutSize_, OutT_, BeginIndex_, EndIndex_>
		(
			to_project_,
			plane_normal_
		);
	}

	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ProjSize_, typename ProjT_, std::size_t NormSize_, typename NormT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<ProjSize_, OutT_> vector_project_plane
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<NormSize_, NormT_>& plane_normal_
	)
	{
		return _vector_underlying::_vector_project_plane<EmuCore::do_subtract, EmuCore::do_multiply, EmuCore::do_reciprocal, ProjSize_, OutT_, BeginIndex_, EndIndex_>
		(
			to_project_,
			plane_normal_
		);
	}

	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ProjSize_, typename ProjT_, std::size_t NormSize_, typename NormT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point> vector_project_plane
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<NormSize_, NormT_>& plane_normal_
	)
	{
		using proj_fp = typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point;
		return _vector_underlying::_vector_project_plane<EmuCore::do_subtract, EmuCore::do_multiply, EmuCore::do_reciprocal, OutSize_, proj_fp, BeginIndex_, EndIndex_>
		(
			to_project_,
			plane_normal_
		);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename ProjT_, typename NormT_, std::size_t ProjSize_, std::size_t NormSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<ProjSize_, typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point> vector_project_plane
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<NormSize_, NormT_>& plane_normal_
	)
	{
		using proj_fp = typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point;
		return _vector_underlying::_vector_project_plane<EmuCore::do_subtract, EmuCore::do_multiply, EmuCore::do_reciprocal, ProjSize_, proj_fp, BeginIndex_, EndIndex_>
		(
			to_project_,
			plane_normal_
		);
	}
#pragma endregion

#pragma region PROJECT_PLANE_3D_CONSTEXPR_FUNCS
	/// <summary>
	/// <para> Calculates the resulting Vector from a projection of the Vector to_project_ onto the 3D plane defined by the passed 3 points </para>
	/// <para>
	///		PlaneReadOffset_: Inclusive index at which to start reading the plane points. Defaults to 0.  
	///		This offset does not apply to reads from to_project_, which will always read from 0.
	/// </para>
	/// <para> If a normal for the defined plane is already available, it is recommended to use vector_project_plane with that normal to minimise normalisation costs. </para>
	/// <para> Unlike most EmuMath Vector functions, if no OutSize_ is provided this will always default to 3 instead of ProjSize_, due to its 3D focus. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="to_project_">: EmuMath Vector to project onto the defined plane.</param>
	/// <param name="plane_point_a_">: Cartesian point a defining the plane to project onto. For more information on how this is used, see vector_normal_to_plane_3d.</param>
	/// <param name="plane_point_b_">: Cartesian point b defining the plane to project onto. For more information on how this is used, see vector_normal_to_plane_3d.</param>
	/// <param name="plane_point_c_">: Cartesian point c defining the plane to project onto. For more information on how this is used, see vector_normal_to_plane_3d.</param>
	/// <returns>EmuMath Vector resulting from the projection of to_project_ onto the plane defined by the passed 3 points.</returns>
	template
	<
		std::size_t OutSize_,
		typename OutT_,
		std::size_t PlaneReadOffset_ = 0,
		std::size_t ProjSize_,
		typename ProjT_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_,
		std::size_t SizeC_,
		typename TC_
	>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_project_plane_3d_constexpr
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<SizeA_, TA_>& plane_point_a_,
		const EmuMath::Vector<SizeB_, TB_>& plane_point_b_,
		const EmuMath::Vector<SizeC_, TC_>& plane_point_c_
	)
	{
		return _vector_underlying::_vector_project_plane_3d
		<
			EmuCore::do_sqrt_constexpr,
			EmuCore::do_subtract,
			EmuCore::do_multiply,
			EmuCore::do_reciprocal,
			OutSize_,
			OutT_,
			PlaneReadOffset_
		>(to_project_, plane_point_a_, plane_point_b_, plane_point_c_);
	}

	template
	<
		typename OutT_,
		std::size_t PlaneReadOffset_ = 0,
		std::size_t ProjSize_,
		typename ProjT_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_,
		std::size_t SizeC_,
		typename TC_
	>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> vector_project_plane_3d_constexpr
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<SizeA_, TA_>& plane_point_a_,
		const EmuMath::Vector<SizeB_, TB_>& plane_point_b_,
		const EmuMath::Vector<SizeC_, TC_>& plane_point_c_
	)
	{
		return _vector_underlying::_vector_project_plane_3d
		<
			EmuCore::do_sqrt_constexpr,
			EmuCore::do_subtract,
			EmuCore::do_multiply,
			EmuCore::do_reciprocal,
			3,
			OutT_,
			PlaneReadOffset_
		>(to_project_, plane_point_a_, plane_point_b_, plane_point_c_);
	}

	template
	<
		std::size_t OutSize_,
		std::size_t PlaneReadOffset_ = 0,
		std::size_t ProjSize_,
		typename ProjT_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_,
		std::size_t SizeC_,
		typename TC_
	>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point> vector_project_plane_3d_constexpr
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<SizeA_, TA_>& plane_point_a_,
		const EmuMath::Vector<SizeB_, TB_>& plane_point_b_,
		const EmuMath::Vector<SizeC_, TC_>& plane_point_c_
	)
	{
		using proj_fp = typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point;
		return _vector_underlying::_vector_project_plane_3d
		<
			EmuCore::do_sqrt_constexpr,
			EmuCore::do_subtract,
			EmuCore::do_multiply,
			EmuCore::do_reciprocal,
			OutSize_,
			proj_fp,
			PlaneReadOffset_
		>(to_project_, plane_point_a_, plane_point_b_, plane_point_c_);
	}

	template
	<
		std::size_t ProjSize_,
		typename ProjT_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_,
		std::size_t SizeC_,
		typename TC_
	>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point> vector_project_plane_3d_constexpr
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<SizeA_, TA_>& plane_point_a_,
		const EmuMath::Vector<SizeB_, TB_>& plane_point_b_,
		const EmuMath::Vector<SizeC_, TC_>& plane_point_c_
	)
	{
		using proj_fp = typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point;
		return _vector_underlying::_vector_project_plane_3d
		<
			EmuCore::do_sqrt_constexpr,
			EmuCore::do_subtract,
			EmuCore::do_multiply,
			EmuCore::do_reciprocal,
			3,
			proj_fp,
			0
		>(to_project_, plane_point_a_, plane_point_b_, plane_point_c_);
	}
#pragma endregion

#pragma region PROJECT_PLANE_3D_FUNCS
	/// <summary>
	/// <para> Calculates the resulting Vector from a projection of the Vector to_project_ onto the 3D plane defined by the passed 3 points </para>
	/// <para>
	///		PlaneReadOffset_: Inclusive index at which to start reading the plane points. Defaults to 0.  
	///		This offset does not apply to reads from to_project_, which will always read from 0.
	/// </para>
	/// <para> If a normal for the defined plane is already available, it is recommended to use vector_project_plane with that normal to minimise normalisation costs. </para>
	/// <para> Unlike most EmuMath Vector functions, if no OutSize_ is provided this will always default to 3 instead of ProjSize_, due to its 3D focus. </para>
	/// <para> For a guarantee to be constexpr-evaluable if possible, use vector_project_plane_3d_constexpr instead. </para>
	/// </summary>
	/// <param name="to_project_">: EmuMath Vector to project onto the defined plane.</param>
	/// <param name="plane_point_a_">: Cartesian point a defining the plane to project onto. For more information on how this is used, see vector_normal_to_plane_3d.</param>
	/// <param name="plane_point_b_">: Cartesian point b defining the plane to project onto. For more information on how this is used, see vector_normal_to_plane_3d.</param>
	/// <param name="plane_point_c_">: Cartesian point c defining the plane to project onto. For more information on how this is used, see vector_normal_to_plane_3d.</param>
	/// <returns>EmuMath Vector resulting from the projection of to_project_ onto the plane defined by the passed 3 points.</returns>
	template
	<
		std::size_t OutSize_,
		typename OutT_,
		std::size_t PlaneReadOffset_ = 0,
		std::size_t ProjSize_,
		typename ProjT_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_,
		std::size_t SizeC_,
		typename TC_
	>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_project_plane_3d
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<SizeA_, TA_>& plane_point_a_,
		const EmuMath::Vector<SizeB_, TB_>& plane_point_b_,
		const EmuMath::Vector<SizeC_, TC_>& plane_point_c_
	)
	{
		return _vector_underlying::_vector_project_plane_3d
		<
			EmuCore::do_sqrt,
			EmuCore::do_subtract,
			EmuCore::do_multiply,
			EmuCore::do_reciprocal,
			OutSize_,
			OutT_,
			PlaneReadOffset_
		>(to_project_, plane_point_a_, plane_point_b_, plane_point_c_);
	}

	template
	<
		typename OutT_,
		std::size_t PlaneReadOffset_ = 0,
		std::size_t ProjSize_,
		typename ProjT_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_,
		std::size_t SizeC_,
		typename TC_
	>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> vector_project_plane_3d
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<SizeA_, TA_>& plane_point_a_,
		const EmuMath::Vector<SizeB_, TB_>& plane_point_b_,
		const EmuMath::Vector<SizeC_, TC_>& plane_point_c_
	)
	{
		return _vector_underlying::_vector_project_plane_3d
		<
			EmuCore::do_sqrt,
			EmuCore::do_subtract,
			EmuCore::do_multiply,
			EmuCore::do_reciprocal,
			3,
			OutT_,
			PlaneReadOffset_
		>(to_project_, plane_point_a_, plane_point_b_, plane_point_c_);
	}

	template
	<
		std::size_t OutSize_,
		std::size_t PlaneReadOffset_ = 0,
		std::size_t ProjSize_,
		typename ProjT_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_,
		std::size_t SizeC_,
		typename TC_
	>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point> vector_project_plane_3d
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<SizeA_, TA_>& plane_point_a_,
		const EmuMath::Vector<SizeB_, TB_>& plane_point_b_,
		const EmuMath::Vector<SizeC_, TC_>& plane_point_c_
	)
	{
		using proj_fp = typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point;
		return _vector_underlying::_vector_project_plane_3d
		<
			EmuCore::do_sqrt,
			EmuCore::do_subtract,
			EmuCore::do_multiply,
			EmuCore::do_reciprocal,
			OutSize_,
			proj_fp,
			PlaneReadOffset_
		>(to_project_, plane_point_a_, plane_point_b_, plane_point_c_);
	}

	template
	<
		std::size_t ProjSize_,
		typename ProjT_,
		std::size_t SizeA_,
		typename TA_,
		std::size_t SizeB_,
		typename TB_,
		std::size_t SizeC_,
		typename TC_
	>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point> vector_project_plane_3d
	(
		const EmuMath::Vector<ProjSize_, ProjT_>& to_project_,
		const EmuMath::Vector<SizeA_, TA_>& plane_point_a_,
		const EmuMath::Vector<SizeB_, TB_>& plane_point_b_,
		const EmuMath::Vector<SizeC_, TC_>& plane_point_c_
	)
	{
		using proj_fp = typename EmuMath::Vector<ProjSize_, ProjT_>::preferred_floating_point;
		return _vector_underlying::_vector_project_plane_3d
		<
			EmuCore::do_sqrt,
			EmuCore::do_subtract,
			EmuCore::do_multiply,
			EmuCore::do_reciprocal,
			3,
			proj_fp,
			0
		>(to_project_, plane_point_a_, plane_point_b_, plane_point_c_);
	}
#pragma endregion
}

#endif
