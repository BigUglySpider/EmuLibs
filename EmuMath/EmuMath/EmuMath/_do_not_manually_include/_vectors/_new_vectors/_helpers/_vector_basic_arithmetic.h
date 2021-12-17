#ifndef EMU_MATH_NEW_VECTOR_BASIC_ARITHMETIC_H_INC_
#define EMU_MATH_NEW_VECTOR_BASIC_ARITHMETIC_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../../EmuCore/Functors/Arithmetic.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Outputs a negated form of the provided EmuMath Vector, with the output Vector using the provided OutSize_ and OutT_ template arguments. </para>
	/// <para> OutSize_: Optional argument used as the Size_ argument for the output EmuMath Vector type. Defaults to the input Vector's Size_. </para>
	/// <para> OutT_: Optional argument used as the T_ argument for the output EmuMath Vector type. Defaults to the input Vector's T_. </para>
	/// </summary>
	/// <param name="in_vector_">EmuMath Vector to output the negated form of.</param>
	/// <returns>Negated form of in_vector_ (i.e. -in_vector_) as an EmuMath Vector type formed from the provided OutSize_ and OutT_ arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_negate(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<typename OutT_, std::size_t Size_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_negate(const EmuMath::NewVector<Size_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_negate<typename EmuMath::NewVector<Size_, InT_>::value_type_uq>,
			EmuMath::NewVector<Size_, OutT_>,
			0,
			EmuMath::NewVector<Size_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_negate
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			0,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>::size,
			0
		>(in_vector_);
	}
	template<typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_negate
	(
		const EmuMath::NewVector<Size_, T_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_negate<typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			0,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>::size,
			0
		>(in_vector_);
	}
}

#endif
