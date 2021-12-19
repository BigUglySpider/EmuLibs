#ifndef EMU_MATH_NEW_VECTOR_BASIC_ARITHMETIC_H_INC_
#define EMU_MATH_NEW_VECTOR_BASIC_ARITHMETIC_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../../EmuCore/Functors/Arithmetic.h"

namespace EmuMath::Helpers
{
#pragma region NEGATION
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
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_negate
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

	/// <summary>
	/// <para> Outputs a negated form of the provided in_vector_ to the provided out_vector_. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="in_vector_">EmuMath Vector to output the negated form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_negate(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		_vector_underlying::_vector_mutate_no_func_passed
		<
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(out_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a copy of the provided in_vector_, with values within the provided index range negated. </para>
	/// <para> BeginIndex_ is the inclusive index at which to start writing negated values to the output Vector. </para>
	/// <para> EndIndex_ is the exclusive index at which to stop writing negated values to the output Vector. </para>
	/// </summary>
	/// <param name="in_vector_">EmuMath Vector to copy, with negated values within the specified index range.</param>
	/// <returns>EmuMath Vector copy of the provided in_vector_, formed with the provided OutSize_ and OutT_ args, with indices in the specified range negated. </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_negate_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_partial_mutation_copy_args_only
		<
			OutSize_,
			OutT_,
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			const EmuMath::NewVector<InSize_, InT_>&,
			BeginIndex_,
			EndIndex_,
			BeginIndex_
		>(in_vector_, in_vector_);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_negate_range
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_partial_mutation_copy_args_only
		<
			OutSize_,
			typename EmuMath::NewVector<InSize_, InT_>::value_type_uq,
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			const EmuMath::NewVector<InSize_, InT_>&,
			BeginIndex_,
			EndIndex_,
			BeginIndex_
		>(in_vector_, in_vector_);
	}	
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_negate_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_partial_mutation_copy_args_only
		<
			InSize_,
			OutT_,
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			const EmuMath::NewVector<InSize_, InT_>&,
			BeginIndex_,
			EndIndex_,
			BeginIndex_
		>(in_vector_, in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_negate_range
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_partial_mutation_copy_args_only
		<
			InSize_,
			typename EmuMath::NewVector<InSize_, InT_>::value_type_uq,
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			const EmuMath::NewVector<InSize_, InT_>&,
			BeginIndex_,
			EndIndex_,
			BeginIndex_
		>(in_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a copy of the provided in_vector_ to out_vector_, with values within the provided index range negated. </para>
	/// <para> BeginIndex_ is the inclusive index at which to start writing negated values to the output Vector. </para>
	/// <para> EndIndex_ is the exclusive index at which to stop writing negated values to the output Vector. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to write copied and negated values to.</param>
	/// <param name="in_vector_">EmuMath Vector to copy, with negated values within the specified index range.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_negate_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		_vector_underlying::_vector_partial_mutation_copy_no_func_passed
		<
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			const EmuMath::NewVector<InSize_, InT_>&,
			BeginIndex_,
			EndIndex_,
			BeginIndex_
		>(out_vector_, in_vector_, in_vector_);
	}

	/// <summary>
	/// <para>
	///		Outputs a partial negated copy of the provided in_vector_ to an output vector with template arguments OutSize_ and OutT_, 
	///		which are optional and default to the Size_ and T_ arguments of in_vector_.
	/// </para>
	/// <para> Non-negated indices in the output Vector will be default constructed. </para>
	/// <para> OutBegin_ is the inclusve index at which to start writing negated values to the output Vector. </para>
	/// <para> OutEnd_ is the exclusive index at which to stop writing negated values to the output Vector. </para>
	/// <para> 
	///		NegateBegin_ is the inclusive index at which to start reading values from in_vector_ in order to negate. 
	///		This is incremented per mutation, but is not changed when not in the negation range. 
	/// </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to read elements from when performing negations.</param>
	/// <returns>EmuMath Vector with negated values from the specified indices of in_vector_ within the OutBegin_:OutEnd_ range, and default values elsewhere.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NegateBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_negate_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			OutBegin_,
			OutEnd_,
			NegateBegin_
		>(in_vector_);
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NegateBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_negate_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<InSize_, OutT_>,
			OutBegin_,
			OutEnd_,
			NegateBegin_
		>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NegateBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_negate_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			OutBegin_,
			OutEnd_,
			NegateBegin_
		>(in_vector_);
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NegateBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_negate_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			OutBegin_,
			OutEnd_,
			NegateBegin_
		>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a partial negated copy of the provided in_vector_ to the provided out_vector_ </para>
	/// <para> Indices in out_vector_ not in the spcified range will not be modified. </para>
	/// <para> OutBegin_ is the inclusve index at which to start writing negated values to the output Vector. </para>
	/// <para> OutEnd_ is the exclusive index at which to stop writing negated values to the output Vector. </para>
	/// <para> 
	///		NegateBegin_ is the inclusive index at which to start reading values from in_vector_ in order to negate. 
	///		This is incremented per mutation, but is not changed when not in the negation range. 
	/// </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to write negated elements to.</param>
	/// <param name="in_vector_">: EmuMath Vector to read elements from when performing negations.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NegateBegin_ = 0, typename OutT_, std::size_t OutSize_, typename InT_, std::size_t InSize_>
	constexpr inline void new_vector_negate_range_no_copy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		_vector_underlying::_vector_mutate_no_func_passed
		<
			EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			OutBegin_,
			OutEnd_,
			NegateBegin_
		>(out_vector_, in_vector_);
	}
#pragma endregion
}

#endif


