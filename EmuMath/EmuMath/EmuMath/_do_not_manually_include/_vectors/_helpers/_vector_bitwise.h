#ifndef EMU_MATH_vector_BITWISE_H_INC_
#define EMU_MATH_vector_BITWISE_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../EmuCore/Functors/Bitwise.h"

// Contains:
// --- bitwise_not
// --- bitwise_and
// --- bitwise_or
// --- btiwise_xor
// --- shift_left
// --- shift_right

namespace EmuMath::Helpers
{
#pragma region BITWISE_NOT_FUNCS
	/// <summary>
	/// <para> Outputs the result of a bitwise NOT on the provided EmuMath Vector, with the output Vector using the provided OutSize_ and OutT_ template arguments. </para>
	/// </summary>
	/// <param name="in_vector_">EmuMath Vector to perform the bitwise NOT operation on.</param>
	/// <returns>Result of a bitwise NOT of the passed Vector, as an EmuMath Vector type formed from the provided OutSize_ and OutT_ arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_bitwise_not(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_bitwise_not<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION(Func_, OutSize_, OutT_, InSize_, InT_)(in_vector_);
	}
	template<typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> vector_bitwise_not(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_bitwise_not<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION(Func_, InSize_, OutT_, InSize_, InT_)(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	vector_bitwise_not(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_bitwise_not<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION(Func_, OutSize_, in_value_uq, InSize_, InT_)(in_vector_);
	}
	template<typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	vector_bitwise_not(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_bitwise_not<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION(Func_, InSize_, in_value_uq, InSize_, InT_)(in_vector_);
	}

	/// <summary>
	/// <para> Outputs the result of a bitwise NOT on the provided EmuMath Vector, via the provided out_vector_. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="in_vector_">EmuMath Vector to perform the bitwise NOT operation on.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void vector_bitwise_not(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_bitwise_not<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_REF(Func_, OutSize_, OutT_, InSize_, InT_)(out_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a copy of the provided in_vector_, with values within the provided index range using the result of a bitwise NOT of said indices. </para>
	/// <para> BeginIndex_ is the inclusive index at which to start writing bitwise NOT results to the output Vector. </para>
	/// <para> EndIndex_ is the exclusive index at which to stop writing bitwise NOT results to the output Vector. </para>
	/// </summary>
	/// <param name="in_vector_">EmuMath Vector to perform the bitwise NOT operation on within the specified index range.</param>
	/// <returns>
	///		EmuMath Vector copy of the provided in_vector_, formed with the provided OutSize_ and OutT_ args,
	///		with indices in the specified range using bitwise NOT results.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_bitwise_not_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_bitwise_not<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE(Func_, OutSize_, OutT_, InSize_, InT_, BeginIndex_, EndIndex_)(in_vector_, in_vector_);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> vector_bitwise_not_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_bitwise_not<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE(Func_, InSize_, OutT_, InSize_, InT_, BeginIndex_, EndIndex_)(in_vector_, in_vector_);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	vector_bitwise_not_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_bitwise_not<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE(Func_, OutSize_, in_value_uq, InSize_, InT_, BeginIndex_, EndIndex_)(in_vector_, in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	vector_bitwise_not_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_bitwise_not<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE(Func_, InSize_, in_value_uq, InSize_, InT_, BeginIndex_, EndIndex_)(in_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a copy of the provided in_vector_ to out_vector_, with values within the provided index range using the result of a bitwise NOT of said indices. </para>
	/// <para> BeginIndex_ is the inclusive index at which to start writing bitwise NOT results to the output Vector. </para>
	/// <para> EndIndex_ is the exclusive index at which to stop writing bitwise NOT results to the output Vector. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to write copied and bitwise NOT result values to.</param>
	/// <param name="in_vector_">EmuMath Vector to perform the bitwise NOT operation on within the specified index range.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void vector_bitwise_not_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_bitwise_not<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		EMU_MATH_VECTOR_MUTATION_REF_RANGE(Func_, OutT_, OutSize_, InSize_, InT_, BeginIndex_, EndIndex_, BeginIndex_)(out_vector_, in_vector_, in_vector_);
	}

	/// <summary>
	/// <para>
	///		Outputs a partial bitwise NOT-ed copy of the provided in_vector_ to an output vector with template arguments OutSize_ and OutT_, 
	///		which are optional and default to the Size_ and T_ arguments of in_vector_.
	/// </para>
	/// <para> Non-converted indices in the output Vector will be default constructed. </para>
	/// <para> OutBegin_ is the inclusve index at which to start writing bitwise NOT results to the output Vector. </para>
	/// <para> OutEnd_ is the exclusive index at which to stop writing bitwise NOT results to the output Vector. </para>
	/// <para> 
	///		NotBegin_ is the inclusive index at which to start reading values from in_vector_ in order to perform bitwise NOT operations. 
	///		This is incremented per mutation, but is not changed when not in the bitwise NOT range. 
	/// </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to read elements from when performing bitwise NOT operations.</param>
	/// <returns>EmuMath Vector with bitwise NOT results from the specified indices of in_vector_ within the OutBegin_:OutEnd_ range, and default values elsewhere.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NotBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_bitwise_not_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_bitwise_not<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(Func_, OutSize_, OutT_, InSize_, InT_, OutBegin_, OutEnd_, NotBegin_)(in_vector_);
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NotBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> vector_bitwise_not_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_bitwise_not<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(Func_, InSize_, OutT_, InSize_, InT_, OutBegin_, OutEnd_, NotBegin_)(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NotBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
		vector_bitwise_not_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_bitwise_not<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(Func_, OutSize_, in_value_uq, InSize_, InT_, OutBegin_, OutEnd_, NotBegin_)(in_vector_);
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NotBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
		vector_bitwise_not_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_bitwise_not<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(Func_, InSize_, in_value_uq, InSize_, InT_, OutBegin_, OutEnd_, NotBegin_)(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a partial bitwise NOT-ed copy of the provided in_vector_ to the provided out_vector_ </para>
	/// <para> Indices in out_vector_ not in the specified range will not be modified. </para>
	/// <para> OutBegin_ is the inclusve index at which to start writing bitwise NOT results to the output Vector. </para>
	/// <para> OutEnd_ is the exclusive index at which to stop writing bitwise NOT results to the output Vector. </para>
	/// <para> 
	///		NotBegin_ is the inclusive index at which to start reading values from in_vector_ in order to perform bitwise NOT operations. 
	///		This is incremented per mutation, but is not changed when not in the bitwise NOT range. 
	/// </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to write bitwise NOT results to.</param>
	/// <param name="in_vector_">: EmuMath Vector to read elements from when performing bitwise NOT operations.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NotBegin_, typename OutT_, std::size_t OutSize_, typename InT_, std::size_t InSize_>
	constexpr inline void vector_bitwise_not_range_no_copy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_bitwise_not<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_REF_RANGE_NO_COPY(Func_, OutSize_, OutT_, InSize_, InT_, OutBegin_, OutEnd_, NotBegin_)(out_vector_, in_vector_);
	}
#pragma endregion

#pragma region BITWISE_AND_FUNCS
	/// <summary>
	/// <para> Returns the results of bitwise ANDing vector_lhs_ and rhs_ as the desired EmuMath Vector type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be ANDed. Otherwise, all elements in vector_lhs_ will have rhs_ ANDed. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of ANDing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of ANDing.</param>
	/// <returns>EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), containing AND results.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_bitwise_and(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_bitwise_and, OutSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_bitwise_and(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_bitwise_and, LhsSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_and
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_bitwise_and, OutSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename Rhs_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_and
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_bitwise_and, LhsSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of ANDing vector_lhs_ and rhs_ to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be ANDed. Otherwise, all elements in vector_lhs_ will have rhs_ ANDed. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of ANDing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of ANDing.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	constexpr inline void vector_bitwise_and(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_bitwise_and, OutSize_, OutT_)(out_vector_, vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range ANDed with rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be ANDed. Otherwise, all elements in vector_lhs_ will have rhs_ ANDed. </para>
	/// <para> BeginIndex_: Inclusive index at which to start ANDing elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop ANDing elements. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of ANDing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of ANDing.</param>
	/// <returns>Copy of vector_lhs_, with ANDing performed with the provided rhs_ as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_bitwise_and_range(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_bitwise_and, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_bitwise_and_range(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_bitwise_and, LhsSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_and_range
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_bitwise_and, OutSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_and_range
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_bitwise_and, LhsSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range ANDed with rhs_, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be ANDed. Otherwise, all elements in vector_lhs_ will have rhs_ ANDed. </para>
	/// <para> BeginIndex_: Inclusive index at which to start ANDing elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop ANDing elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of ANDing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of ANDing.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_bitwise_and_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_> vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_bitwise_and, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs the results of ANDing vector_lhs_ and rhs_ to the specified index range of an output vector, starting from vector_lhs_ index AndBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be ANDed. Otherwise, all elements in vector_lhs_ will have rhs_ ANDed. </para>
	/// <para> Indices outside of the specified output range will be default-constructed. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing bitwise operation results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing bitwise operation results to the output Vector. </para>
	/// <para> AndBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform bitwise operations. </para>
	/// </summary>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of ANDing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of ANDing.</param>
	/// <returns>
	///		EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), 
	///		containing the results of ANDing in the specified index range as described, and default values outside of said range.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AndBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_bitwise_and_range_no_copy(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_and, OutSize_, OutT_, OutBegin_, OutEnd_, AndBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AndBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_bitwise_and_range_no_copy(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_and, LhsSize_, OutT_, OutBegin_, OutEnd_, AndBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AndBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_and_range_no_copy
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_and, OutSize_, lhs_value_uq, OutBegin_, OutEnd_, AndBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AndBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_and_range_no_copy
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_and, LhsSize_, lhs_value_uq, OutBegin_, OutEnd_, AndBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of bitwise ANDing vector_lhs_ and rhs_ to the specified index range of the passed out_vector_, starting from vector_lhs_ index AndBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be ANDed. Otherwise, all elements in vector_lhs_ will have rhs_ ANDed. </para>
	/// <para> Indices outside of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing bitwise operation results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing bitwise operation results to the output Vector. </para>
	/// <para> AndBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform bitwise operations. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of ANDing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of ANDing.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AndBegin_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_bitwise_and_range_no_copy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_and, OutSize_, OutT_, OutBegin_, OutEnd_, AndBegin_)
		(
			out_vector_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region BITWISE_OR_FUNCS
	/// <summary>
	/// <para> Returns the results of bitwise ORing vector_lhs_ and rhs_ as the desired EmuMath Vector type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be ORed. Otherwise, all elements in vector_lhs_ will have rhs_ ORed. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of ORing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of ORing.</param>
	/// <returns>EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), containing OR results.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_bitwise_or(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_bitwise_or, OutSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_bitwise_or(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_bitwise_or, LhsSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_or
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_bitwise_or, OutSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename Rhs_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_or
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_bitwise_or, LhsSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of ORing vector_lhs_ and rhs_ to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be ORed. Otherwise, all elements in vector_lhs_ will have rhs_ ORed. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of ORing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of ORing.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	constexpr inline void vector_bitwise_or(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_bitwise_or, OutSize_, OutT_)(out_vector_, vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range ORed with rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be ORed. Otherwise, all elements in vector_lhs_ will have rhs_ ORed. </para>
	/// <para> BeginIndex_: Inclusive index at which to start ORing elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop ORing elements. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of ORing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of ORing.</param>
	/// <returns>Copy of vector_lhs_, with ORing performed with the provided rhs_ as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_bitwise_or_range(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_bitwise_or, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_bitwise_or_range(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_bitwise_or, LhsSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_or_range
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_bitwise_or, OutSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_or_range
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_bitwise_or, LhsSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range ORed with rhs_, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be ORed. Otherwise, all elements in vector_lhs_ will have rhs_ ORed. </para>
	/// <para> BeginIndex_: Inclusive index at which to start ORing elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop ORing elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of ORing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of ORing.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_bitwise_or_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_> vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_bitwise_or, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs the results of ORing vector_lhs_ and rhs_ to the specified index range of an output vector, starting from vector_lhs_ index OrBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be ORed. Otherwise, all elements in vector_lhs_ will have rhs_ ORed. </para>
	/// <para> Indices outside of the specified output range will be default-constructed. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing bitwise operation results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing bitwise operation results to the output Vector. </para>
	/// <para> OrBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform bitwise operations. </para>
	/// </summary>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of ORing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of ORing.</param>
	/// <returns>
	///		EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), 
	///		containing the results of ORing in the specified index range as described, and default values outside of said range.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t OrBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_bitwise_or_range_no_copy(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_or, OutSize_, OutT_, OutBegin_, OutEnd_, OrBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t OrBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_bitwise_or_range_no_copy(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_or, LhsSize_, OutT_, OutBegin_, OutEnd_, OrBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t OrBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_or_range_no_copy
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_or, OutSize_, lhs_value_uq, OutBegin_, OutEnd_, OrBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t OrBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_or_range_no_copy
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_or, LhsSize_, lhs_value_uq, OutBegin_, OutEnd_, OrBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of bitwise ORing vector_lhs_ and rhs_ to the specified index range of the passed out_vector_, starting from vector_lhs_ index OrBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be ORed. Otherwise, all elements in vector_lhs_ will have rhs_ ORed. </para>
	/// <para> Indices outside of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing bitwise operation results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing bitwise operation results to the output Vector. </para>
	/// <para> OrBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform bitwise operations. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of ORing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of ORing.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t OrBegin_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_bitwise_or_range_no_copy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_or, OutSize_, OutT_, OutBegin_, OutEnd_, OrBegin_)
		(
			out_vector_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region BITWISE_XOR_FUNCS
	/// <summary>
	/// <para> Returns the results of bitwise XORing vector_lhs_ and rhs_ as the desired EmuMath Vector type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be XORed. Otherwise, all elements in vector_lhs_ will have rhs_ XORed. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of XORing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of XORing.</param>
	/// <returns>EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), containing XOR results.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_bitwise_xor(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_bitwise_xor, OutSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_bitwise_xor(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_bitwise_xor, LhsSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_xor
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_bitwise_xor, OutSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename Rhs_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_xor
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_bitwise_xor, LhsSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of XORing vector_lhs_ and rhs_ to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be XORed. Otherwise, all elements in vector_lhs_ will have rhs_ XORed. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of XORing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of XORing.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	constexpr inline void vector_bitwise_xor(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_bitwise_xor, OutSize_, OutT_)(out_vector_, vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range XORed with rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be XORed. Otherwise, all elements in vector_lhs_ will have rhs_ XORed. </para>
	/// <para> BeginIndex_: Inclusive index at which to start XORing elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop XORing elements. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of XORing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of XORing.</param>
	/// <returns>Copy of vector_lhs_, with XORing performed with the provided rhs_ as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_bitwise_xor_range(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_bitwise_xor, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_bitwise_xor_range(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_bitwise_xor, LhsSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_xor_range
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_bitwise_xor, OutSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_xor_range
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_bitwise_xor, LhsSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range XORed with rhs_, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be XORed. Otherwise, all elements in vector_lhs_ will have rhs_ XORed. </para>
	/// <para> BeginIndex_: Inclusive index at which to start XORing elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop XORing elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of XORing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of XORing.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_bitwise_xor_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_> vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_bitwise_xor, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs the results of XORing vector_lhs_ and rhs_ to the specified index range of an output vector, starting from vector_lhs_ index XorBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be XORed. Otherwise, all elements in vector_lhs_ will have rhs_ XORed. </para>
	/// <para> Indices outside of the specified output range will be default-constructed. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing bitwise operation results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing bitwise operation results to the output Vector. </para>
	/// <para> XorBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform bitwise operations. </para>
	/// </summary>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of XORing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of XORing.</param>
	/// <returns>
	///		EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), 
	///		containing the results of XORing in the specified index range as described, and default values outside of said range.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t XorBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_bitwise_xor_range_no_copy(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_xor, OutSize_, OutT_, OutBegin_, OutEnd_, XorBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t XorBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_bitwise_xor_range_no_copy(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_xor, LhsSize_, OutT_, OutBegin_, OutEnd_, XorBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t XorBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_xor_range_no_copy
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_xor, OutSize_, lhs_value_uq, OutBegin_, OutEnd_, XorBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t XorBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_bitwise_xor_range_no_copy
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_xor, LhsSize_, lhs_value_uq, OutBegin_, OutEnd_, XorBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of XORing vector_lhs_ and rhs_ to the specified index range of the passed out_vector_, starting from vector_lhs_ index XorBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be XORed. Otherwise, all elements in vector_lhs_ will have rhs_ XORed. </para>
	/// <para> Indices outside of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing bitwise operation results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing bitwise operation results to the output Vector. </para>
	/// <para> XorBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform bitwise operations. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of XORing.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of XORing.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t XorBegin_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_bitwise_xor_range_no_copy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_bitwise_xor, OutSize_, OutT_, OutBegin_, OutEnd_, XorBegin_)
		(
			out_vector_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region SHIFT_LEFT_FUNCS
	/// <summary>
	/// <para> Returns the results of left-shifting vector_lhs_ using rhs_ as the desired EmuMath Vector type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be used for shifting. Otherwise, all elements in vector_lhs_ will use rhs_ directly. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of the shift operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of the shift operation.</param>
	/// <returns>EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), containing shift results.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_shift_left(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_left_shift, OutSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_shift_left(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_left_shift, LhsSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_shift_left
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_left_shift, OutSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename Rhs_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_shift_left
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_left_shift, LhsSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns the results of left-shifting vector_lhs_ using rhs_, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be used for shifting. Otherwise, all elements in vector_lhs_ will use rhs_ directly. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of the shift operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of the shift operation.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	constexpr inline void vector_shift_left(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_left_shift, OutSize_, OutT_)(out_vector_, vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range left-shifted using rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be used for shifting. Otherwise, all elements in vector_lhs_ will use rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start shifting elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop shifting elements. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of the shift operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of the shift operation.</param>
	/// <returns>Copy of vector_lhs_, with shifting performed with the provided rhs_ as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_shift_left_range(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_left_shift, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_shift_left_range(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_left_shift, LhsSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_shift_left_range
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_left_shift, OutSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_shift_left_range
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_left_shift, LhsSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range left-shifted using rhs_, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be used for shifting. Otherwise, all elements in vector_lhs_ will use rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start shifting elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop shifting elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of the shift operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of the shift operation.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_shift_left_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_> vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_left_shift, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs the results of left-shifting vector_lhs_ using rhs_ to the specified index range of an output vector, starting from vector_lhs_ index ShiftBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be used for shifting. Otherwise, all elements in vector_lhs_ will use rhs_ directly. </para>
	/// <para> Indices outside of the specified output range will be default-constructed. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing shift operation results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing shift operation results to the output Vector. </para>
	/// <para> ShiftBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform shift operations. </para>
	/// </summary>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of the shift operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of the shift operation.</param>
	/// <returns>
	///		EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), 
	///		containing the results of the shift operation in the specified index range as described, and default values outside of said range.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_shift_left_range_no_copy(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_left_shift, OutSize_, OutT_, OutBegin_, OutEnd_, ShiftBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_shift_left_range_no_copy(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_left_shift, LhsSize_, OutT_, OutBegin_, OutEnd_, ShiftBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_shift_left_range_no_copy
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_left_shift, OutSize_, lhs_value_uq, OutBegin_, OutEnd_, ShiftBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_shift_left_range_no_copy
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_left_shift, LhsSize_, lhs_value_uq, OutBegin_, OutEnd_, ShiftBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para>
	///		Outputs the results of left-shifting vector_lhs_ using rhs_ to the specified index range of the passed out_vector_,
	/// starting from vector_lhs_ index ShiftBegin_.
	/// </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be used for shifting. Otherwise, all elements in vector_lhs_ will use rhs_ directly. </para>
	/// <para> Indices outside of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing shift operation results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing shift operation results to the output Vector. </para>
	/// <para> ShiftBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform shift operations. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of the shift operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of the shift operation.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_shift_left_range_no_copy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_left_shift, OutSize_, OutT_, OutBegin_, OutEnd_, ShiftBegin_)
		(
			out_vector_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region SHIFT_RIGHT_FUNCS
	/// <summary>
	/// <para> Returns the results of right-shifting vector_lhs_ using rhs_ as the desired EmuMath Vector type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be used for shifting. Otherwise, all elements in vector_lhs_ will use rhs_ directly. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of the shift operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of the shift operation.</param>
	/// <returns>EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), containing shift results.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_shift_right(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_right_shift, OutSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_shift_right(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_right_shift, LhsSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_shift_right
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_right_shift, OutSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename Rhs_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_shift_right
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_right_shift, LhsSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns the results of right-shifting vector_lhs_ using rhs_, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be used for shifting. Otherwise, all elements in vector_lhs_ will use rhs_ directly. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of the shift operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of the shift operation.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	constexpr inline void vector_shift_right(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_right_shift, OutSize_, OutT_)(out_vector_, vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range right-shifted using rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be used for shifting. Otherwise, all elements in vector_lhs_ will use rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start shifting elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop shifting elements. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of the shift operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of the shift operation.</param>
	/// <returns>Copy of vector_lhs_, with shifting performed with the provided rhs_ as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_shift_right_range(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_right_shift, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_shift_right_range(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_right_shift, LhsSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_shift_right_range
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_right_shift, OutSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_shift_right_range
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_right_shift, LhsSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range right-shifted using rhs_, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be used for shifting. Otherwise, all elements in vector_lhs_ will use rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start shifting elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop shifting elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of the shift operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of the shift operation.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_shift_right_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_> vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_right_shift, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs the results of right-shifting vector_lhs_ using rhs_ to the specified index range of an output vector, starting from vector_lhs_ index ShiftBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be used for shifting. Otherwise, all elements in vector_lhs_ will use rhs_ directly. </para>
	/// <para> Indices outside of the specified output range will be default-constructed. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing shift operation results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing shift operation results to the output Vector. </para>
	/// <para> ShiftBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform shift operations. </para>
	/// </summary>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of the shift operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of the shift operation.</param>
	/// <returns>
	///		EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), 
	///		containing the results of the shift operation in the specified index range as described, and default values outside of said range.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> vector_shift_right_range_no_copy(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_right_shift, OutSize_, OutT_, OutBegin_, OutEnd_, ShiftBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> vector_shift_right_range_no_copy(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_right_shift, LhsSize_, OutT_, OutBegin_, OutEnd_, ShiftBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_shift_right_range_no_copy
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_right_shift, OutSize_, lhs_value_uq, OutBegin_, OutEnd_, ShiftBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> vector_shift_right_range_no_copy
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_right_shift, LhsSize_, lhs_value_uq, OutBegin_, OutEnd_, ShiftBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para>
	///		Outputs the results of right-shifting vector_lhs_ using rhs_ to the specified index range of the passed out_vector_, 
	///		starting from vector_lhs_ index ShiftBegin_.
	/// </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be used for shifting. Otherwise, all elements in vector_lhs_ will use rhs_ directly. </para>
	/// <para> Indices outside of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing shift operation results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing shift operation results to the output Vector. </para>
	/// <para> ShiftBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform shift operations. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of the shift operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of the shift operation.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ShiftBegin_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_shift_right_range_no_copy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_right_shift, OutSize_, OutT_, OutBegin_, OutEnd_, ShiftBegin_)
		(
			out_vector_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion
}

#endif
