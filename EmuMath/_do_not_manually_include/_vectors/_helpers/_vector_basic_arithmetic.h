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
// --- fmadd
// --- fmsub

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
	/// <para> Indices outside of the specified output range will be default-constructed. </para>
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
	/// <para> Indices outside of the specified output range will not be modified. </para>
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
	/// <para> Indices outside of the specified output range will be default-constructed. </para>
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
	/// <para> Indices outside of the specified output range will not be modified. </para>
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
	[[nodiscard]] constexpr inline auto vector_multiply(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
		-> std::enable_if_t<!EmuMath::TMP::is_emu_matrix_v<Rhs_>, EmuMath::Vector<OutSize_, OutT_>>
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_multiply, OutSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline auto vector_multiply(const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
		-> std::enable_if_t<!EmuMath::TMP::is_emu_matrix_v<Rhs_>, EmuMath::Vector<LhsSize_, OutT_>>
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_multiply, LhsSize_, OutT_)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<std::size_t OutSize_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline auto vector_multiply
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	) -> std::enable_if_t<!EmuMath::TMP::is_emu_matrix_v<Rhs_>, EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>>
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_multiply, OutSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}
	template<typename Rhs_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline auto vector_multiply
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_,
		Rhs_&& rhs_
	) -> std::enable_if_t<!EmuMath::TMP::is_emu_matrix_v<Rhs_>, EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>>
	{
		using lhs_value_uq = typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_multiply, LhsSize_, lhs_value_uq)(vector_lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Outputs the results of multiplying vector_lhs_ by rhs_ to the provided out_vector_. </para>
	/// <para>
	///		If Rhs_ is an EmuMath Vector: Respective elements in each Vector will be multiplied. 
	///		Otherwise, all elements in vector_lhs_ will be multiplied by rhs_.
	/// </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_lhs_">: EmuMath Vector appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of multiplication.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
	constexpr inline auto vector_multiply(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<LhsSize_, LhsT_>& vector_lhs_, Rhs_&& rhs_)
		-> std::enable_if_t<!EmuMath::TMP::is_emu_matrix_v<Rhs_>, void>
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
	/// <para> Indices outside of the specified output range will be default-constructed. </para>
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
	/// <para> Indices outside of the specified output range will not be modified. </para>
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
	/// <para> Indices outside of the specified output range will be default-constructed. </para>
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
	/// <para> Indices outside of the specified output range will not be modified. </para>
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
	/// <para> Indices outside of the specified output range will be default-constructed. </para>
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
	/// <para> Indices outside of the specified output range will not be modified. </para>
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

#pragma region FMA_FUNCS
	/// <summary>
	/// <para> Outputs the result of a fused multiply-add operation with the provided vector_x_, y_, and z_ arguments. </para>
	/// <para> This operation will perform only one floating-point round operation; the intermediate from vector_x_ * y_ is unrounded. </para>
	/// <para> If Y_ is an EmuMath Vector: Respective elements in vector_x_ and y_ will be multiplied. Otherwise, all elements in vector_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
	///		Otherwise, all intermediate multiplication results will have z_ added directly.
	/// </para>
	/// </summary>
	/// <param name="vector_x_">: EmuMath Vector to perform the fused multiply-add operation on.</param>
	/// <param name="y_">: Scalar or EmuMath Vector to multiply vector_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Vector to add to intermediate multiplication results.</param>
	/// <returns>EmuMath Vector containing the results of a fused multiply-add operation with the provided arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_fmadd(const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_fmadd, OutSize_, OutT_)(vector_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	template<typename OutT_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeX_, OutT_> vector_fmadd(const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_fmadd, SizeX_, OutT_)(vector_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	template<std::size_t OutSize_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeX_, TX_>::value_type_uq> vector_fmadd
	(
		const EmuMath::Vector<SizeX_, TX_>& vector_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_value_uq = typename EmuMath::Vector<SizeX_, TX_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_fmadd, OutSize_, x_value_uq)(vector_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	template<typename TX_, class Y_, class Z_, std::size_t SizeX_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeX_, typename EmuMath::Vector<SizeX_, TX_>::value_type_uq> vector_fmadd
	(
		const EmuMath::Vector<SizeX_, TX_>& vector_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_value_uq = typename EmuMath::Vector<SizeX_, TX_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_fmadd, SizeX_, x_value_uq)(vector_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	/// <summary>
	/// <para> Outputs the result of a fused multiply-add operation with the provided vector_x_, y_, and z_ arguments, via the provided out_vector_. </para>
	/// <para> This operation will perform only one floating-point round operation; the intermediate from vector_x_ * y_ is unrounded. </para>
	/// <para> If Y_ is an EmuMath Vector: Respective elements in vector_x_ and y_ will be multiplied. Otherwise, all elements in vector_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
	///		Otherwise, all intermediate multiplication results will have z_ added directly.
	/// </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_x_">: EmuMath Vector to perform the fused multiply-add operation on.</param>
	/// <param name="y_">: Scalar or EmuMath Vector to multiply vector_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Vector to add to intermediate multiplication results.</param>
	template<class Y_, class Z_, std::size_t SizeX_, typename TX_, std::size_t OutSize_, typename OutT_>
	constexpr inline void vector_fmadd(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_fmadd, OutSize_, OutT_)(out_vector_, vector_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_x_ as the desired EmuMath Vector type, with fused multiply-add operations performed in the provided range. </para>
	/// <para> When a fmadd operation is performed, it will perform only one floating-point round operation; the intermediate from vector_x_ * y_ is unrounded. </para>
	/// <para> If Y_ is an EmuMath Vector: Respective elements in vector_x_ and y_ will be multiplied. Otherwise, all elements in vector_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
	///		Otherwise, all intermediate multiplication results will have z_ added directly.
	/// </para>
	/// <para> BeginIndex_: Inclusive index at which to start fused multiply-adding elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop fused multiply-adding elements. </para>
	/// </summary>
	/// <param name="vector_x_">: EmuMath Vector to copy, and to perform fused multiply-add operations on within the provided range.</param>
	/// <param name="y_">: Scalar or EmuMath Vector to multiply vector_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Vector to add to intermediate multiplication results.</param>
	/// <returns>Copy of vector_x_, with fused multiply-addition performed with the provided y_ and z_ arguments as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_fmadd_range(const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_fmadd, OutSize_, OutT_, SizeX_, TX_, BeginIndex_, EndIndex_)
		(
			vector_x_,
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeX_, OutT_> vector_fmadd_range(const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_fmadd, SizeX_, OutT_, SizeX_, TX_, BeginIndex_, EndIndex_)
		(
			vector_x_,
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeX_, TX_>::value_type_uq> vector_fmadd_range
	(
		const EmuMath::Vector<SizeX_, TX_>& vector_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_value_uq = typename EmuMath::Vector<SizeX_, TX_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_fmadd, OutSize_, x_value_uq, SizeX_, TX_, BeginIndex_, EndIndex_)
		(
			vector_x_,
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeX_, typename EmuMath::Vector<SizeX_, TX_>::value_type_uq> vector_fmadd_range
	(
		const EmuMath::Vector<SizeX_, TX_>& vector_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_value_uq = typename EmuMath::Vector<SizeX_, TX_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_fmadd, SizeX_, x_value_uq, SizeX_, TX_, BeginIndex_, EndIndex_)
		(
			vector_x_,
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_x_, with fused multiply-add operations performed in the provided range, via the provided out_vector_. </para>
	/// <para> When a fmadd operation is performed, it will perform only one floating-point round operation; the intermediate from vector_x_ * y_ is unrounded. </para>
	/// <para> If Y_ is an EmuMath Vector: Respective elements in vector_x_ and y_ will be multiplied. Otherwise, all elements in vector_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
	///		Otherwise, all intermediate multiplication results will have z_ added directly.
	/// </para>
	/// <para> BeginIndex_: Inclusive index at which to start fused multiply-adding elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop fused multiply-adding elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_x_">: EmuMath Vector to copy, and to perform fused multiply-add operations on within the provided range.</param>
	/// <param name="y_">: Scalar or EmuMath Vector to multiply vector_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Vector to add to intermediate multiplication results.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Y_, class Z_, std::size_t SizeX_, typename TX_, std::size_t OutSize_, typename OutT_>
	constexpr inline void vector_fmadd_range(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_fmadd, OutSize_, OutT_, SizeX_, TX_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_x_,
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	/// <summary>
	/// <para> 
	///		Outputs the results of a fused multiply-add on vector_x_ with the provided y_ and z_ arguments to the specified index range of an output vector, 
	///		starting from index AddBegin_ within any provided input Vectors.
	/// </para>
	/// <para> When a fmadd operation is performed, it will perform only one floating-point round operation; the intermediate from vector_x_ * y_ is unrounded. </para>
	/// <para> If Y_ is an EmuMath Vector: Respective elements in vector_x_ and y_ will be multiplied. Otherwise, all elements in vector_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
	///		Otherwise, all intermediate multiplication results will have z_ added directly.
	/// </para>
	/// <para> Indices outside of the specified output range will be default-constructed. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing fused arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing fused arithmetic results to the output Vector. </para>
	/// <para> FmaddBegin_: Inclusive index at which to start reading elements from vector_x_ (and y_ and z_ if they are EmuMath Vectors) to perform arithmetic. </para>
	/// </summary>
	/// <param name="vector_x_">: EmuMath Vector to perform the fused multiply-add operation on.</param>
	/// <param name="y_">: Scalar or EmuMath Vector to multiply vector_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Vector to add to intermediate multiplication results.</param>
	/// <returns>
	///		EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), 
	///		containing the results of fused multiply-addition in the specified index range as described, and default values outside of said range.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmaddBegin_, typename TX_, std::size_t SizeX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_fmadd_range_no_copy(const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_fmadd, OutSize_, OutT_, OutBegin_, OutEnd_, FmaddBegin_)
		(
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmaddBegin_, typename TX_, std::size_t SizeX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeX_, OutT_> vector_fmadd_range_no_copy(const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_fmadd, SizeX_, OutT_, OutBegin_, OutEnd_, FmaddBegin_)
		(
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmaddBegin_, typename TX_, std::size_t SizeX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeX_, TX_>::value_type_uq> vector_fmadd_range_no_copy
	(
		const EmuMath::Vector<SizeX_, TX_>& vector_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_value_uq = typename EmuMath::Vector<SizeX_, TX_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_fmadd, OutSize_, x_value_uq, OutBegin_, OutEnd_, FmaddBegin_)
		(
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmaddBegin_, typename TX_, std::size_t SizeX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeX_, typename EmuMath::Vector<SizeX_, TX_>::value_type_uq> vector_fmadd_range_no_copy
	(
		const EmuMath::Vector<SizeX_, TX_>& vector_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_value_uq = typename EmuMath::Vector<SizeX_, TX_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_fmadd, SizeX_, x_value_uq, OutBegin_, OutEnd_, FmaddBegin_)
		(
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	/// <summary>
	/// <para> 
	///		Outputs the results of a fused multiply-add on vector_x_ with the provided y_ and z_ arguments to the specified index range of the provided out_vector_, 
	///		starting from index AddBegin_ within any provided input Vectors (excluding out_vector_).
	/// </para>
	/// <para> When a fmadd operation is performed, it will perform only one floating-point round operation; the intermediate from vector_x_ * y_ is unrounded. </para>
	/// <para> If Y_ is an EmuMath Vector: Respective elements in vector_x_ and y_ will be multiplied. Otherwise, all elements in vector_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
	///		Otherwise, all intermediate multiplication results will have z_ added directly.
	/// </para>
	/// <para> Indices outside of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing fused arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing fused arithmetic results to the output Vector. </para>
	/// <para> FmaddBegin_: Inclusive index at which to start reading elements from vector_x_ (and y_ and z_ if they are EmuMath Vectors) to perform arithmetic. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to otuput to.</param>
	/// <param name="vector_x_">: EmuMath Vector to perform the fused multiply-add operation on.</param>
	/// <param name="y_">: Scalar or EmuMath Vector to multiply vector_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Vector to add to intermediate multiplication results.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmaddBegin_, class Y_, class Z_, std::size_t SizeX_, typename TX_, std::size_t OutSize_, typename OutT_>
	constexpr inline void vector_fmadd_range_no_copy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_fmadd, OutSize_, OutT_, OutBegin_, OutEnd_, FmaddBegin_)
		(
			out_vector_,
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}
#pragma endregion

	#pragma region FMA_FUNCS
	/// <summary>
	/// <para> Outputs the result of a fused multiply-subtract operation with the provided vector_x_, y_, and z_ arguments. </para>
	/// <para> This operation will perform only one floating-point round operation; the intermediate from vector_x_ * y_ is unrounded. </para>
	/// <para> If Y_ is an EmuMath Vector: Respective elements in vector_x_ and y_ will be multiplied. Otherwise, all elements in vector_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
	///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
	/// </para>
	/// </summary>
	/// <param name="vector_x_">: EmuMath Vector to perform the fused multiply-subtract operation on.</param>
	/// <param name="y_">: Scalar or EmuMath Vector to multiply vector_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Vector to subtract from intermediate multiplication results.</param>
	/// <returns>EmuMath Vector containing the results of a fused multiply-subtract operation with the provided arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_fmsub(const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_fmsub, OutSize_, OutT_)(vector_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	template<typename OutT_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeX_, OutT_> vector_fmsub(const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_fmsub, SizeX_, OutT_)(vector_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	template<std::size_t OutSize_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeX_, TX_>::value_type_uq> vector_fmsub
	(
		const EmuMath::Vector<SizeX_, TX_>& vector_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_value_uq = typename EmuMath::Vector<SizeX_, TX_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_fmsub, OutSize_, x_value_uq)(vector_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	template<typename TX_, class Y_, class Z_, std::size_t SizeX_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeX_, typename EmuMath::Vector<SizeX_, TX_>::value_type_uq> vector_fmsub
	(
		const EmuMath::Vector<SizeX_, TX_>& vector_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_value_uq = typename EmuMath::Vector<SizeX_, TX_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_fmsub, SizeX_, x_value_uq)(vector_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	/// <summary>
	/// <para> Outputs the result of a fused multiply-subtract operation with the provided vector_x_, y_, and z_ arguments, via the provided out_vector_. </para>
	/// <para> This operation will perform only one floating-point round operation; the intermediate from vector_x_ * y_ is unrounded. </para>
	/// <para> If Y_ is an EmuMath Vector: Respective elements in vector_x_ and y_ will be multiplied. Otherwise, all elements in vector_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
	///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
	/// </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_x_">: EmuMath Vector to perform the fused multiply-subtracted operation on.</param>
	/// <param name="y_">: Scalar or EmuMath Vector to multiply vector_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Vector to subtract from intermediate multiplication results.</param>
	template<class Y_, class Z_, std::size_t SizeX_, typename TX_, std::size_t OutSize_, typename OutT_>
	constexpr inline void vector_fmsub(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_fmsub, OutSize_, OutT_)(out_vector_, vector_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	/// <summary>
	/// <para> Outputs a copy of vector_x_ as the desired EmuMath Vector type, with fused multiply-subtract operations performed in the provided range. </para>
	/// <para> When a fmsub operation is performed, it will perform only one floating-point round operation; the intermediate from vector_x_ * y_ is unrounded. </para>
	/// <para> If Y_ is an EmuMath Vector: Respective elements in vector_x_ and y_ will be multiplied. Otherwise, all elements in vector_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
	///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
	/// </para>
	/// <para> BeginIndex_: Inclusive index at which to start fused multiply-subtracting elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop fused multiply-subtracting elements. </para>
	/// </summary>
	/// <param name="vector_x_">: EmuMath Vector to copy, and to perform fused multiply-subtract operations on within the provided range.</param>
	/// <param name="y_">: Scalar or EmuMath Vector to multiply vector_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Vector to subtract from intermediate multiplication results.</param>
	/// <returns>Copy of vector_x_, with fused multiply-subtraction performed with the provided y_ and z_ arguments as described within the specified index range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_fmsub_range(const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_fmsub, OutSize_, OutT_, SizeX_, TX_, BeginIndex_, EndIndex_)
		(
			vector_x_,
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeX_, OutT_> vector_fmsub_range(const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_fmsub, SizeX_, OutT_, SizeX_, TX_, BeginIndex_, EndIndex_)
		(
			vector_x_,
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeX_, TX_>::value_type_uq> vector_fmsub_range
	(
		const EmuMath::Vector<SizeX_, TX_>& vector_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_value_uq = typename EmuMath::Vector<SizeX_, TX_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_fmsub, OutSize_, x_value_uq, SizeX_, TX_, BeginIndex_, EndIndex_)
		(
			vector_x_,
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t SizeX_, typename TX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeX_, typename EmuMath::Vector<SizeX_, TX_>::value_type_uq> vector_fmsub_range
	(
		const EmuMath::Vector<SizeX_, TX_>& vector_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_value_uq = typename EmuMath::Vector<SizeX_, TX_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_fmsub, SizeX_, x_value_uq, SizeX_, TX_, BeginIndex_, EndIndex_)
		(
			vector_x_,
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	/// <summary>
	/// <para> Outputs a copy of vector_x_, with fused multiply-subtract operations performed in the provided range, via the provided out_vector_. </para>
	/// <para> When a fmsub operation is performed, it will perform only one floating-point round operation; the intermediate from vector_x_ * y_ is unrounded. </para>
	/// <para> If Y_ is an EmuMath Vector: Respective elements in vector_x_ and y_ will be multiplied. Otherwise, all elements in vector_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
	///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
	/// </para>
	/// <para> BeginIndex_: Inclusive index at which to start fused multiply-subtracting elements. </para>
	/// <para> EndIndex_: Exclusive index at which to stop fused multiply-subtracting elements. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_x_">: EmuMath Vector to copy, and to perform fused multiply-subtract operations on within the provided range.</param>
	/// <param name="y_">: Scalar or EmuMath Vector to multiply vector_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Vector to subtract from intermediate multiplication results.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Y_, class Z_, std::size_t SizeX_, typename TX_, std::size_t OutSize_, typename OutT_>
	constexpr inline void vector_fmsub_range(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_fmsub, OutSize_, OutT_, SizeX_, TX_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_x_,
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	/// <summary>
	/// <para> 
	///		Outputs the results of a fused multiply-subtract on vector_x_ with the provided y_ and z_ arguments to the specified index range of an output vector, 
	///		starting from index FmsubBegin_ within any provided input Vectors.
	/// </para>
	/// <para> When a fmsub operation is performed, it will perform only one floating-point round operation; the intermediate from vector_x_ * y_ is unrounded. </para>
	/// <para> If Y_ is an EmuMath Vector: Respective elements in vector_x_ and y_ will be multiplied. Otherwise, all elements in vector_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
	///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
	/// </para>
	/// <para> Indices outside of the specified output range will be default-constructed. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing fused arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing fused arithmetic results to the output Vector. </para>
	/// <para> FmaddBegin_: Inclusive index at which to start reading elements from vector_x_ (and y_ and z_ if they are EmuMath Vectors) to perform fused arithmetic. </para>
	/// </summary>
	/// <param name="vector_x_">: EmuMath Vector to perform the fused multiply-subtract operation on.</param>
	/// <param name="y_">: Scalar or EmuMath Vector to multiply vector_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Vector to subtract from intermediate multiplication results.</param>
	/// <returns>
	///		EmuMath Vector of the desired OutSize_ (defaults to LhsSize_) and OutT_ (defaults to vector_lhs_'s value_type_uq), 
	///		containing the results of fused multiply-subtraction in the specified index range as described, and default values outside of said range.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmsubBegin_, typename TX_, std::size_t SizeX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> vector_fmsub_range_no_copy(const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_fmsub, OutSize_, OutT_, OutBegin_, OutEnd_, FmsubBegin_)
		(
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmsubBegin_, typename TX_, std::size_t SizeX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeX_, OutT_> vector_fmsub_range_no_copy(const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_fmsub, SizeX_, OutT_, OutBegin_, OutEnd_, FmsubBegin_)
		(
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmsubBegin_, typename TX_, std::size_t SizeX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Vector<SizeX_, TX_>::value_type_uq> vector_fmsub_range_no_copy
	(
		const EmuMath::Vector<SizeX_, TX_>& vector_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_value_uq = typename EmuMath::Vector<SizeX_, TX_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_fmsub, OutSize_, x_value_uq, OutBegin_, OutEnd_, FmsubBegin_)
		(
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmsubBegin_, typename TX_, std::size_t SizeX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Vector<SizeX_, typename EmuMath::Vector<SizeX_, TX_>::value_type_uq> vector_fmsub_range_no_copy
	(
		const EmuMath::Vector<SizeX_, TX_>& vector_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_value_uq = typename EmuMath::Vector<SizeX_, TX_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_fmsub, SizeX_, x_value_uq, OutBegin_, OutEnd_, FmsubBegin_)
		(
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	/// <summary>
	/// <para> 
	///		Outputs the results of a fused multiply-subtract on vector_x_ with the provided y_ and z_ arguments to the specified index range of the provided out_vector_, 
	///		starting from index AddBegin_ within any provided input Vectors (excluding out_vector_).
	/// </para>
	/// <para> When a fmsub operation is performed, it will perform only one floating-point round operation; the intermediate from vector_x_ * y_ is unrounded. </para>
	/// <para> If Y_ is an EmuMath Vector: Respective elements in vector_x_ and y_ will be multiplied. Otherwise, all elements in vector_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Vector: Intermediate results from each multiplication in specific indices will have the respective indices of z_ subtracted. 
	///		Otherwise, all intermediate multiplication results will have z_ subtracted directly.
	/// </para>
	/// <para> Indices outside of the specified output range will not be modified. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing fused arithmetic results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing fused arithmetic results to the output Vector. </para>
	/// <para> FmsubBegin_: Inclusive index at which to start reading elements from vector_x_ (and y_ and z_ if they are EmuMath Vectors) to perform fused arithmetic. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to otuput to.</param>
	/// <param name="vector_x_">: EmuMath Vector to perform the fused multiply-subtract operation on.</param>
	/// <param name="y_">: Scalar or EmuMath Vector to multiply vector_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Vector to subtract from intermediate multiplication results.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t FmsubBegin_, class Y_, class Z_, std::size_t SizeX_, typename TX_, std::size_t OutSize_, typename OutT_>
	constexpr inline void vector_fmsub_range_no_copy(EmuMath::Vector<OutSize_, OutT_>& out_vector_, const EmuMath::Vector<SizeX_, TX_>& vector_x_, Y_&& y_, Z_&& z_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_fmsub, OutSize_, OutT_, OutBegin_, OutEnd_, FmsubBegin_)
		(
			out_vector_,
			vector_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}
#pragma endregion
}

#endif

