#ifndef EMU_MATH_NEW_VECTOR_CAST_H_INC_
#define EMU_MATH_NEW_VECTOR_CAST_H_INC_ 1

#include "_common_vector_helpers.h"

// Contains:
// --- cast

namespace EmuMath::Helpers
{
#pragma region CONST_CASTS
	/// <summary>
	/// <para> Casts the passed EmuMath Vector to an EmuMath Vector of the specified OutSize_ and OutT_. </para>
	/// <para> OutSize_: Size of the output Vector. If not provided, this will default to the input Vector's Size_ arg. </para>
	/// <para> OutT_: Typearg for the output Vector. If not provided, this will default to the input Vector's value_type_uq. </para>
	/// <para> At least 1 of OutSize_ or OutT_ must be provided. </para>
	/// <para> Offset_: Optional offset at which to start reading the input Vector for forming the output cast. Defaults to 0. </para>
	/// </summary>
	/// <param name="in_vector_">Constant reference to an EmuMath Vector to cast.</param>
	/// <returns>The passed EmuMath Vector cast to the desired output Vector.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_cast(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_cast<OutSize_, OutT_, const EmuMath::NewVector<InSize_, InT_>&, Offset_>(in_vector_);
	}

	template<typename OutT_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_cast(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_cast<InSize_, OutT_, const EmuMath::NewVector<InSize_, InT_>&, Offset_>(in_vector_);
	}

	template<std::size_t OutSize_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_cast
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_cast
		<
			OutSize_,
			typename EmuMath::NewVector<InSize_, InT_>::value_type_uq,
			const EmuMath::NewVector<InSize_, InT_>&,
			Offset_
		>(in_vector_);
	}
#pragma endregion

#pragma region NON_CONST_CASTS
	/// <summary>
	/// <para> Casts the passed EmuMath Vector to an EmuMath Vector of the specified OutSize_ and OutT_. </para>
	/// <para> OutSize_: Size of the output Vector. If not provided, this will default to the input Vector's Size_ arg. </para>
	/// <para> OutT_: Typearg for the output Vector. If not provided, this will default to the input Vector's value_type_uq. </para>
	/// <para> At least 1 of OutSize_ or OutT_ must be provided. </para>
	/// <para> Offset_: Optional offset at which to start reading the input Vector for forming the output cast. Defaults to 0. </para>
	/// </summary>
	/// <param name="in_vector_">Reference to an EmuMath Vector to cast.</param>
	/// <returns>The passed EmuMath Vector cast to the desired output Vector.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_cast(EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_cast<OutSize_, OutT_, EmuMath::NewVector<InSize_, InT_>&, Offset_>(in_vector_);
	}

	template<typename OutT_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_cast(EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_cast<InSize_, OutT_, EmuMath::NewVector<InSize_, InT_>&, Offset_>(in_vector_);
	}

	template<std::size_t OutSize_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_cast
	(
		EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_cast
		<
			OutSize_,
			typename EmuMath::NewVector<InSize_, InT_>::value_type_uq,
			EmuMath::NewVector<InSize_, InT_>&,
			Offset_
		>(in_vector_);
	}
#pragma endregion

#pragma region RVALUE_CASTS
	/// <summary>
	/// <para> Casts the passed EmuMath Vector to an EmuMath Vector of the specified OutSize_ and OutT_. </para>
	/// <para> OutSize_: Size of the output Vector. If not provided, this will default to the input Vector's Size_ arg. </para>
	/// <para> OutT_: Typearg for the output Vector. If not provided, this will default to the input Vector's value_type_uq. </para>
	/// <para> At least 1 of OutSize_ or OutT_ must be provided. </para>
	/// <para> Offset_: Optional offset at which to start reading the input Vector for forming the output cast. Defaults to 0. </para>
	/// </summary>
	/// <param name="in_vector_">Rvalue-reference to an EmuMath Vector to cast.</param>
	/// <returns>The passed EmuMath Vector cast to the desired output Vector.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_cast(EmuMath::NewVector<InSize_, InT_>&& in_vector_)
	{
		return _vector_underlying::_vector_cast<OutSize_, OutT_, EmuMath::NewVector<InSize_, InT_>, Offset_>
		(
			std::forward<EmuMath::NewVector<InSize_, InT_>>(in_vector_)
		);
	}

	template<typename OutT_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_cast(EmuMath::NewVector<InSize_, InT_>&& in_vector_)
	{
		return _vector_underlying::_vector_cast<InSize_, OutT_, EmuMath::NewVector<InSize_, InT_>, Offset_>
		(
			std::forward<EmuMath::NewVector<InSize_, InT_>>(in_vector_)
		);
	}

	template<std::size_t OutSize_, std::size_t Offset_ = 0, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_cast
	(
		EmuMath::NewVector<InSize_, InT_>&& in_vector_
	)
	{
		return _vector_underlying::_vector_cast
		<
			OutSize_,
			typename EmuMath::NewVector<InSize_, InT_>::value_type_uq,
			EmuMath::NewVector<InSize_, InT_>,
			Offset_
		>(std::forward<EmuMath::NewVector<InSize_, InT_>>(in_vector_));
	}
#pragma endregion
}

#endif
