#ifndef EMU_MATH_NEW_VECTOR_BASIC_ARITHMETIC_H_INC_
#define EMU_MATH_NEW_VECTOR_BASIC_ARITHMETIC_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../../EmuCore/Functors/Arithmetic.h"

// CONTAINS:
// --- add

namespace EmuMath::Helpers
{
#pragma region ADD_FUNCS
	/// <summary>
	/// <para> Returns the results of adding vector_lhs_ and rhs_ as the desired EmuMath Vector type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be added. Otherwise, all elements in vector_lhs_ will have rhs_ added. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of addition.</param>
	/// <returns>EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), containing addition results.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_add(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_add, OutSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> new_vector_add(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_add, LhsSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> new_vector_add
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_add, OutSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename Rhs_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> new_vector_add
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_add, LhsSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of adding vector_lhs_ and rhs_ to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be added. Otherwise, all elements in vector_lhs_ will have rhs_ added. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of addition.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	constexpr inline void new_vector_add(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_add, OutSize_, OutT_)(out_vector_, vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with rhs_ added to indices in the specified range. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be added. Otherwise, all added elements in vector_lhs_ will have rhs_ added. </para>
	/// <para> BeginIndex_: Inclusive index at which to start adding elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop adding elements. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of addition.</param>
	/// <returns>Copy of vector_lhs_, with addition performed with the provided rhs_ as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_add_range(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_add, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> new_vector_add_range(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_add, LhsSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> new_vector_add_range
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_add, OutSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> new_vector_add_range
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_add, LhsSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with rhs_ added to indices in the specified range, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be added. Otherwise, all added elements in vector_lhs_ will have rhs_ added. </para>
	/// <para> BeginIndex_: Inclusive index at which to start adding elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop adding elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of addition.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void new_vector_add_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_> vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_add, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs the results of adding vector_lhs_ and rhs_ to the specified index range of an output vector, starting from vector_lhs_ index AddBegin_. </para>
	/// <para> Indices outisde of the specified output range will be default-constructed. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
	/// <para> AddBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
	/// </summary>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of addition.</param>
	/// <returns>
	///		EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), 
	///		containing the results of addition in the specified index range as described, and default values outside of said range.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_add_range_no_copy(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_add, OutSize_, OutT_, OutBegin_, OutEnd_, AddBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, OutT_> new_vector_add_range_no_copy(const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_add, LhsSize_, OutT_, OutBegin_, OutEnd_, AddBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> new_vector_add_range_no_copy
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_add, OutSize_, lhs_value_uq, OutBegin_, OutEnd_, AddBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<LhsSize_, typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq> new_vector_add_range_no_copy
	(
		const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::NewVector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_add, LhsSize_, lhs_value_uq, OutBegin_, OutEnd_, AddBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of adding vector_lhs_ and rhs_ to the specified index range of the passed out_vector_, starting from vector_lhs_ index AddBegin_. </para>
	/// <para> Indices outisde of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
	/// <para> AddBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of addition.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void new_vector_add_range_no_copy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_add, OutSize_, OutT_, OutBegin_, OutEnd_, AddBegin_)
		(
			out_vector_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion
}

#endif


