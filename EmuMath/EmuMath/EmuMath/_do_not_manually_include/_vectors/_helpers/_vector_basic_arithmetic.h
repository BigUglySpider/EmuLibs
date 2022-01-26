#ifndef EMU_MATH_VECTOR_BASIC_ARITHMETIC_H_INC_
#define EMU_MATH_VECTOR_BASIC_ARITHMETIC_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../EmuCore/Functors/Arithmetic.h"

// CONTAINS:
// --- add
// --- subtract
// --- multiply
// --- divide
// --- mod

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
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_add(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_add, OutSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_add(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_add, LhsSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_add
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_add, OutSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename Rhs_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_add
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
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
	constexpr inline void vector_add(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_add, OutSize_, OutT_)(out_vector_, vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with rhs_ added to indices in the specified range. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be added. Otherwise, all elements in vector_lhs_ will have rhs_ added. </para>
	/// <para> BeginIndex_: Inclusive index at which to start adding elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop adding elements. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of addition.</param>
	/// <returns>Copy of vector_lhs_, with addition performed with the provided rhs_ as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_add_range(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_add, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_add_range(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_add, LhsSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_add_range
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_add, OutSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_add_range
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_add, LhsSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with rhs_ added to indices in the specified range, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be added. Otherwise, all elements in vector_lhs_ will have rhs_ added. </para>
	/// <para> BeginIndex_: Inclusive index at which to start adding elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop adding elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of addition.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_add_range(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_> vector_lhs_, Rhs_&& rhs_)
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
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be added. Otherwise, all elements in vector_lhs_ will have rhs_ added. </para>
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
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_add_range_no_copy(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_add, OutSize_, OutT_, OutBegin_, OutEnd_, AddBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_add_range_no_copy(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_add, LhsSize_, OutT_, OutBegin_, OutEnd_, AddBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_add_range_no_copy
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_add, OutSize_, lhs_value_uq, OutBegin_, OutEnd_, AddBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_add_range_no_copy
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_add, LhsSize_, lhs_value_uq, OutBegin_, OutEnd_, AddBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of adding vector_lhs_ and rhs_ to the specified index range of the passed out_vector_, starting from vector_lhs_ index AddBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be added. Otherwise, all elements in vector_lhs_ will have rhs_ added. </para>
	/// <para> Indices outisde of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
	/// <para> AddBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of addition.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AddBegin_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_add_range_no_copy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_add, OutSize_, OutT_, OutBegin_, OutEnd_, AddBegin_)
		(
			out_vector_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region SUBTRACT_FUNCS
	/// <summary>
	/// <para> Returns the results of subtracting rhs_ from vector_lhs_ as the desired EmuMath Vector type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be subtracted. Otherwise, all elements in vector_lhs_ will have rhs_ subtracted. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of subtraction.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of subtraction.</param>
	/// <returns>EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), containing subtraction results.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_subtract(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_subtract, OutSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_subtract(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_subtract, LhsSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_subtract
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_subtract, OutSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename Rhs_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_subtract
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_subtract, LhsSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of subtracting rhs_ from vector_lhs_ to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be subtracted. Otherwise, all elements in vector_lhs_ will have rhs_ subtracted. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of subtraction.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of subtraction.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	constexpr inline void vector_subtract(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_subtract, OutSize_, OutT_)(out_vector_, vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with rhs_ subtracted from indices in the specified range. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be subtracted. Otherwise, all elements in vector_lhs_ will have rhs_ subtracted. </para>
	/// <para> BeginIndex_: Inclusive index at which to start subtracting elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop subtracting elements. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of subtraction.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of subtraction.</param>
	/// <returns>Copy of vector_lhs_, with subtraction performed with the provided rhs_ as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_subtract_range(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_subtract, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_subtract_range(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_subtract, LhsSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_subtract_range
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_subtract, OutSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_subtract_range
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_subtract, LhsSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with rhs_ subtracted from indices in the specified range, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be subtracted. Otherwise, all elements in vector_lhs_ will have rhs_ subtracted. </para>
	/// <para> BeginIndex_: Inclusive index at which to start subtracting elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop subtracting elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of subtraction.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of subtraction.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_subtract_range(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_> vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_subtract, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs the results of subtracting rhs_ from vector_lhs_ to the specified index range of an output vector, starting from vector_lhs_ index AddBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be subtracted. Otherwise, all elements in vector_lhs_ will have rhs_ subtracted. </para>
	/// <para> Indices outisde of the specified output range will be default-constructed. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
	/// <para> SubBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
	/// </summary>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of subtraction.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of subtraction.</param>
	/// <returns>
	///		EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), 
	///		containing the results of subtraction in the specified index range as described, and default values outside of said range.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t SubBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_subtract_range_no_copy(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_subtract, OutSize_, OutT_, OutBegin_, OutEnd_, SubBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t SubBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_subtract_range_no_copy(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_subtract, LhsSize_, OutT_, OutBegin_, OutEnd_, SubBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t SubBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_subtract_range_no_copy
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_subtract, OutSize_, lhs_value_uq, OutBegin_, OutEnd_, SubBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t SubBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_subtract_range_no_copy
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_subtract, LhsSize_, lhs_value_uq, OutBegin_, OutEnd_, SubBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of subtracting rhs_ from vector_lhs_ to the specified index range of the passed out_vector_, starting from vector_lhs_ index AddBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be subtracted. Otherwise, all elements in vector_lhs_ will have rhs_ subtracted. </para>
	/// <para> Indices outisde of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
	/// <para> SubBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of subtraction.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of subtraction.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t SubBegin_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_subtract_range_no_copy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_subtract, OutSize_, OutT_, OutBegin_, OutEnd_, SubBegin_)
		(
			out_vector_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region MULTIPLY_FUNCS
	/// <summary>
	/// <para> Returns the results of multiplying vector_lhs_ by rhs_ as the desired EmuMath Vector type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be multiplied. Otherwise, all elements in vector_lhs_ will be multiplied by rhs_. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of multiplication.</param>
	/// <returns>EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), containing multiplication results.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_multiply(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_multiply, OutSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_multiply(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_multiply, LhsSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_multiply
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_multiply, OutSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename Rhs_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_multiply
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_multiply, LhsSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of multiplying vector_lhs_ by rhs_ to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be multiplied. Otherwise, all elements in vector_lhs_ will be multiplied by rhs_. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of multiplication.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	constexpr inline void vector_multiply(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_multiply, OutSize_, OutT_)(out_vector_, vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range multiplied by rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be multiplied. Otherwise, all elements in vector_lhs_ will be multiplied by rhs_. </para>
	/// <para> BeginIndex_: Inclusive index at which to start multiplying elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop multiplying elements. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of multiplication.</param>
	/// <returns>Copy of vector_lhs_, with multiplication performed with the provided rhs_ as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_multiply_range(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_multiply, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_multiply_range(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_multiply, LhsSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_multiply_range
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_multiply, OutSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_multiply_range
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_multiply, LhsSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range multiplied by rhs_, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be multiplied. Otherwise, all elements in vector_lhs_ will be multiplied by rhs_. </para>
	/// <para> BeginIndex_: Inclusive index at which to start multiplying elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop multiplying elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of multiplication.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_multiply_range(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_> vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_multiply, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs the results of multiplying vector_lhs_ by rhs_ to the specified index range of an output vector, starting from vector_lhs_ index AddBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be multiplied. Otherwise, all elements in vector_lhs_ will be multiplied by rhs_. </para>
	/// <para> Indices outisde of the specified output range will be default-constructed. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
	/// <para> MulBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
	/// </summary>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of multiplication.</param>
	/// <returns>
	///		EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), 
	///		containing the results of multiplication in the specified index range as described, and default values outside of said range.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MulBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_multiply_range_no_copy(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_multiply, OutSize_, OutT_, OutBegin_, OutEnd_, MulBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MulBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_multiply_range_no_copy(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_multiply, LhsSize_, OutT_, OutBegin_, OutEnd_, MulBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MulBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_multiply_range_no_copy
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_multiply, OutSize_, lhs_value_uq, OutBegin_, OutEnd_, MulBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MulBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_multiply_range_no_copy
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_multiply, LhsSize_, lhs_value_uq, OutBegin_, OutEnd_, MulBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of multiplying vector_lhs_ by rhs_ to the specified index range of the passed out_vector_, starting from vector_lhs_ index AddBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be multiplied. Otherwise, all elements in vector_lhs_ will be multiplied by rhs_. </para>
	/// <para> Indices outisde of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
	/// <para> MulBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of multiplication.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MulBegin_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_multiply_range_no_copy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_multiply, OutSize_, OutT_, OutBegin_, OutEnd_, MulBegin_)
		(
			out_vector_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region DIVIDE_FUNCS
	/// <summary>
	/// <para> Returns the results of dividing vector_lhs_ by rhs_ as the desired EmuMath Vector type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be divided. Otherwise, all elements in vector_lhs_ will be divided by rhs_. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of division.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of division.</param>
	/// <returns>EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), containing division results.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_divide(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_divide, OutSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_divide(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_divide, LhsSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_divide
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_divide, OutSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename Rhs_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_divide
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_divide, LhsSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of dividing vector_lhs_ by rhs_ to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be divided. Otherwise, all elements in vector_lhs_ will be divided by rhs_. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of division.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of division.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	constexpr inline void vector_divide(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_divide, OutSize_, OutT_)(out_vector_, vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range divided by rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be divided. Otherwise, all elements in vector_lhs_ will be divided by rhs_. </para>
	/// <para> BeginIndex_: Inclusive index at which to start dividing elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop dividing elements. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of division.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of division.</param>
	/// <returns>Copy of vector_lhs_, with division performed with the provided rhs_ as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_divide_range(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_divide, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_divide_range(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_divide, LhsSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_divide_range
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_divide, OutSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_divide_range
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_divide, LhsSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range divided by rhs_, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be divided. Otherwise, all elements in vector_lhs_ will be divided by rhs_. </para>
	/// <para> BeginIndex_: Inclusive index at which to start dividing elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop dividing elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of division.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of division.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_divide_range(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_> vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_divide, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs the results of dividing vector_lhs_ by rhs_ to the specified index range of an output vector, starting from vector_lhs_ index AddBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be divided. Otherwise, all elements in vector_lhs_ will be divided by rhs_. </para>
	/// <para> Indices outisde of the specified output range will be default-constructed. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
	/// <para> DivBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
	/// </summary>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of division.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of division.</param>
	/// <returns>
	///		EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), 
	///		containing the results of division in the specified index range as described, and default values outside of said range.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t DivBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_divide_range_no_copy(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_divide, OutSize_, OutT_, OutBegin_, OutEnd_, DivBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t DivBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_divide_range_no_copy(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_divide, LhsSize_, OutT_, OutBegin_, OutEnd_, DivBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t DivBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_divide_range_no_copy
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_divide, OutSize_, lhs_value_uq, OutBegin_, OutEnd_, DivBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t DivBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_divide_range_no_copy
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_divide, LhsSize_, lhs_value_uq, OutBegin_, OutEnd_, DivBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of dividing vector_lhs_ by rhs_ to the specified index range of the passed out_vector_, starting from vector_lhs_ index AddBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be divided. Otherwise, all elements in vector_lhs_ will be divided by rhs_. </para>
	/// <para> Indices outisde of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
	/// <para> DivBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of division.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of division.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t DivBegin_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_divide_range_no_copy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_divide, OutSize_, OutT_, OutBegin_, OutEnd_, DivBegin_)
		(
			out_vector_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region MOD_FUNCS
	/// <summary>
	/// <para> Returns the results of modulo-dividing vector_lhs_ by rhs_ as the desired EmuMath Vector type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be divided. Otherwise, all elements in vector_lhs_ will be divided by rhs_. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of modulo-division.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of modulo-division.</param>
	/// <returns>EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), containing modulo-division results.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_mod(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_mod, OutSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_mod(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_mod, LhsSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_mod
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_mod, OutSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename Rhs_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_mod
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_mod, LhsSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of modulo-dividing vector_lhs_ by rhs_ to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be divided. Otherwise, all elements in vector_lhs_ will be divided by rhs_. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of modulo-division.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of modulo-division.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	constexpr inline void vector_mod(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_mod, OutSize_, OutT_)(out_vector_, vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range modulo-divided by rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be divided. Otherwise, all elements in vector_lhs_ will be divided by rhs_. </para>
	/// <para> BeginIndex_: Inclusive index at which to start modulo-dividing elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop modulo-dividing elements. </para>
	/// </summary>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of modulo-division.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of modulo-division.</param>
	/// <returns>Copy of vector_lhs_, with modulo-division performed with the provided rhs_ as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_mod_range(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_mod, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_mod_range(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_mod, LhsSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_mod_range
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_mod, OutSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_mod_range
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_mod, LhsSize_, lhs_value_uq, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_lhs_ as the desired EmuMath Vector type, with indices in the specified range modulo-divided by rhs_, to the provided out_vector_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be divided. Otherwise, all elements in vector_lhs_ will be divided by rhs_. </para>
	/// <para> BeginIndex_: Inclusive index at which to start modulo-dividing elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop modulo-dividing elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector to copy, and appearing on the left-hand side of modulo-division.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of modulo-division.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_mod_range(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_> vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_mod, OutSize_, OutT_, LhsSize_, LhsT_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_lhs_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs the results of modulo-dividing vector_lhs_ by rhs_ to the specified index range of an output vector, starting from vector_lhs_ index AddBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be divided. Otherwise, all elements in vector_lhs_ will be divided by rhs_. </para>
	/// <para> Indices outisde of the specified output range will be default-constructed. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
	/// <para> ModBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
	/// </summary>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of modulo-division.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of modulo-division.</param>
	/// <returns>
	///		EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), 
	///		containing the results of modulo-division in the specified index range as described, and default values outside of said range.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ModBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_mod_range_no_copy(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_mod, OutSize_, OutT_, OutBegin_, OutEnd_, ModBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ModBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, OutT_> vector_mod_range_no_copy(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_mod, LhsSize_, OutT_, OutBegin_, OutEnd_, ModBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ModBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_mod_range_no_copy
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_mod, OutSize_, lhs_value_uq, OutBegin_, OutEnd_, ModBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ModBegin_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq> vector_mod_range_no_copy
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	)
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_mod, LhsSize_, lhs_value_uq, OutBegin_, OutEnd_, ModBegin_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of modulo-dividing vector_lhs_ by rhs_ to the specified index range of the passed out_vector_, starting from vector_lhs_ index AddBegin_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be divided. Otherwise, all elements in vector_lhs_ will be divided by rhs_. </para>
	/// <para> Indices outisde of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing arithmetic results to the output Vector. </para>
	/// <para> ModBegin_: Inclusive index at which to start reading elements from vector_lhs_ (and rhs_ if it is an EmuMath Vector) to perform arithmetic. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">EmuMath Vector appearing on the left-hand side of modulo-division.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of modulo-division.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t ModBegin_, typename OutT_, std::size_t OutSize_, typename LhsT_, std::size_t LhsSize_, typename Rhs_>
	constexpr inline void vector_mod_range_no_copy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_mod, OutSize_, OutT_, OutBegin_, OutEnd_, ModBegin_)
		(
			out_vector_,
			vector_lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion
}

#endif

