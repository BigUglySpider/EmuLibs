#ifndef EMU_MATH_NEW_VECTOR_MISC_ARITHMETIC_H_INC_
#define EMU_MATH_NEW_VECTOR_MISC_ARITHMETIC_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../../EmuCore/Functors/Arithmetic.h"

// CONTAINS:
// --- abs
// --- lerp

namespace EmuMath::Helpers
{
#pragma region ABS_FUNCS
	/// <summary>
	/// <para> Outputs the absolute form of the provided EmuMath Vector, with the output Vector using the provided OutSize_ and OutT_ template arguments. </para>
	/// <para> OutSize_: Optional argument used as the Size_ argument for the output EmuMath Vector type. Defaults to the input Vector's Size_. </para>
	/// <para> OutT_: Optional argument used as the T_ argument for the output EmuMath Vector type. Defaults to the input Vector's T_. </para>
	/// </summary>
	/// <param name="in_vector_">EmuMath Vector to output the absolute form of.</param>
	/// <returns>Absolute form of in_vector_ as an EmuMath Vector type formed from the provided OutSize_ and OutT_ arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_abs(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_abs<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION(Func_, OutSize_, OutT_, InSize_, InT_)(in_vector_);
	}
	template<typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_abs(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_abs<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION(Func_, InSize_, OutT_, InSize_, InT_)(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_abs(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_abs<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION(Func_, OutSize_, in_value_uq, InSize_, InT_)(in_vector_);
	}
	template<typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_abs(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_abs<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION(Func_, InSize_, in_value_uq, InSize_, InT_)(in_vector_);
	}

	/// <summary>
	/// <para> Outputs the absolute form of the provided in_vector_ to the provided out_vector_. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="in_vector_">EmuMath Vector to output the absolute form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_abs(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_abs<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_REF(Func_, OutSize_, OutT_, InSize_, InT_)(out_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a copy of the provided in_vector_, with values within the provided index range converted to their absolute form. </para>
	/// <para> BeginIndex_ is the inclusive index at which to start writing absolute values to the output Vector. </para>
	/// <para> EndIndex_ is the exclusive index at which to stop writing absolute values to the output Vector. </para>
	/// </summary>
	/// <param name="in_vector_">EmuMath Vector to copy, with absolute values within the specified index range.</param>
	/// <returns>EmuMath Vector copy of the provided in_vector_, formed with the provided OutSize_ and OutT_ args, with indices in the specified range made absolute. </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_abs_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_abs<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE(Func_, OutSize_, OutT_, InSize_, InT_, BeginIndex_, EndIndex_)(in_vector_, in_vector_);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_abs_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_abs<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE(Func_, InSize_, OutT_, InSize_, InT_, BeginIndex_, EndIndex_)(in_vector_, in_vector_);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_abs_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_abs<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE(Func_, OutSize_, in_value_uq, InSize_, InT_, BeginIndex_, EndIndex_)(in_vector_, in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_abs_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_abs<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE(Func_, InSize_, in_value_uq, InSize_, InT_, BeginIndex_, EndIndex_)(in_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a copy of the provided in_vector_ to out_vector_, with values within the provided index range converted to their absolute form. </para>
	/// <para> BeginIndex_ is the inclusive index at which to start writing absolute values to the output Vector. </para>
	/// <para> EndIndex_ is the exclusive index at which to stop writing absolute values to the output Vector. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to write copied and absolute values to.</param>
	/// <param name="in_vector_">EmuMath Vector to copy, with absolute values within the specified index range.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_abs_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_abs<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		EMU_MATH_VECTOR_MUTATION_REF_RANGE(Func_, OutT_, OutSize_, InSize_, InT_, BeginIndex_, EndIndex_, BeginIndex_)(out_vector_, in_vector_, in_vector_);
	}

	/// <summary>
	/// <para>
	///		Outputs a partial absolute copy of the provided in_vector_ to an output vector with template arguments OutSize_ and OutT_, 
	///		which are optional and default to the Size_ and T_ arguments of in_vector_.
	/// </para>
	/// <para> Non-converted indices in the output Vector will be default constructed. </para>
	/// <para> OutBegin_ is the inclusve index at which to start writing absolute values to the output Vector. </para>
	/// <para> OutEnd_ is the exclusive index at which to stop writing absolute values to the output Vector. </para>
	/// <para> 
	///		AbsBegin_ is the inclusive index at which to start reading values from in_vector_ in order to perform absolute conversion. 
	///		This is incremented per mutation, but is not changed when not in the absolute conversion range. 
	/// </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to read elements from when performing absolute conversion.</param>
	/// <returns>EmuMath Vector with absolute values from the specified indices of in_vector_ within the OutBegin_:OutEnd_ range, and default values elsewhere.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AbsBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_abs_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_abs<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(Func_, OutSize_, OutT_, InSize_, InT_, OutBegin_, OutEnd_, AbsBegin_)(in_vector_);
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AbsBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_abs_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_abs<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(Func_, InSize_, OutT_, InSize_, InT_, OutBegin_, OutEnd_, AbsBegin_)(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AbsBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_abs_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_abs<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(Func_, OutSize_, in_value_uq, InSize_, InT_, OutBegin_, OutEnd_, AbsBegin_)(in_vector_);
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AbsBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_abs_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_abs<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(Func_, InSize_, in_value_uq, InSize_, InT_, OutBegin_, OutEnd_, AbsBegin_)(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a partial absolute copy of the provided in_vector_ to the provided out_vector_ </para>
	/// <para> Indices in out_vector_ not in the specified range will not be modified. </para>
	/// <para> OutBegin_ is the inclusve index at which to start writing absolute values to the output Vector. </para>
	/// <para> OutEnd_ is the exclusive index at which to stop writing absolute values to the output Vector. </para>
	/// <para> 
	///		AbsBegin_ is the inclusive index at which to start reading values from in_vector_ in order to perform absolute conversion. 
	///		This is incremented per mutation, but is not changed when not in the absolute conversion range. 
	/// </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to write absolute elements to.</param>
	/// <param name="in_vector_">: EmuMath Vector to read elements from when performing absolute conversion.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t AbsBegin_ = 0, typename OutT_, std::size_t OutSize_, typename InT_, std::size_t InSize_>
	constexpr inline void new_vector_abs_range_no_copy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_abs<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_REF_RANGE_NO_COPY(Func_, OutSize_, OutT_, InSize_, InT_, OutBegin_, OutEnd_, AbsBegin_)(out_vector_, in_vector_);
	}
#pragma endregion

#pragma region LERP_FUNCS
	/// <summary>
	/// <para>
	///		Outputs an EmuMath Vector of the provided OutSize and OutT_, containing the results of linearly interpolating vector_a_, b_, and t_, 
	///		where vector_a_ is all starting points, b_ the target point(s), and t_ the interpolation weighting(s).
	/// </para>
	/// <para> If b_ is an EmuMath Vector: Individual output indices will use the respective index in b_ as the target point of interpolation. </para>
	/// <para> If t_ is an EmuMath Vector: Individual output indices will use the respective index in t_ as the interpolation weighting. </para>
	/// <para> If a valid argument type is *not* an EmuMath Vector: All output indices will use that value in every interpolation. </para>
	/// </summary>
	/// <param name="vector_a_">EmuMath Vector used as the starting point of interpolations. a in the equation `a + ((b - a) * t)`.</param>
	/// <param name="b_">Scalar or EmuMath Vector used as the target point of interpolations. b in the equation `a + ((b - a) * t)`.</param>
	/// <param name="t_">Scalar or EmuMath Vector used as the weighting of interpolations. t in the equation `a + ((b - a) * t)`.</param>
	/// <returns>Result of linearly interpolating the provided arguments as described, stored as the desired output Vector type.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t ASize_, typename AT_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_lerp(const EmuMath::NewVector<ASize_, AT_>& vector_a_, B_&& b_, T_&& t_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_lerp, OutSize_, OutT_)(vector_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}
	template<typename OutT_, std::size_t ASize_, typename AT_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<ASize_, OutT_> new_vector_lerp(const EmuMath::NewVector<ASize_, AT_>& vector_a_, B_&& b_, T_&& t_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_lerp, ASize_, OutT_)(vector_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}
	template<std::size_t OutSize_, std::size_t ASize_, typename AT_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<ASize_, AT_>::value_type_uq> new_vector_lerp
	(
		const EmuMath::NewVector<ASize_, AT_>& vector_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_value_uq = typename EmuMath::NewVector<ASize_, AT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_lerp, ASize_, a_value_uq)(vector_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}
	template<class B_, class T_, typename AT_, std::size_t ASize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<ASize_, typename EmuMath::NewVector<ASize_, AT_>::value_type_uq> new_vector_lerp
	(
		const EmuMath::NewVector<ASize_, AT_>& vector_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_value_uq = typename EmuMath::NewVector<ASize_, AT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE(EmuCore::do_lerp, ASize_, a_value_uq)(vector_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}

	/// <summary>
	/// <para>
	///		Outputs the results of linearly interpolating vector_a_, b_, and t_, 
	///		where vector_a_ is all starting points, b_ the target point(s), and t_ the interpolation weighting(s), 
	///		to the provided out_vector_.
	/// </para>
	/// <para> If b_ is an EmuMath Vector: Individual output indices will use the respective index in b_ as the target point of interpolation. </para>
	/// <para> If t_ is an EmuMath Vector: Individual output indices will use the respective index in t_ as the interpolation weighting. </para>
	/// <para> If a valid argument type is *not* an EmuMath Vector: All output indices will use that value in every interpolation. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="vector_a_">EmuMath Vector used as the starting point of interpolations. a in the equation `a + ((b - a) * t)`.</param>
	/// <param name="b_">Scalar or EmuMath Vector used as the target point of interpolations. b in the equation `a + ((b - a) * t)`.</param>
	/// <param name="t_">Scalar or EmuMath Vector used as the weighting of interpolations. t in the equation `a + ((b - a) * t)`.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t ASize_, typename AT_, class B_, class T_>
	[[nodiscard]] constexpr inline void new_vector_lerp(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<ASize_, AT_>& vector_a_, B_&& b_, T_&& t_)
	{
		return EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE(EmuCore::do_lerp, OutSize_, OutT_)(out_vector_, vector_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}

	/// <summary>
	/// <para>
	///		Outputs an EmuMath Vector of the provided OutSize and OutT_, containing the results of linearly interpolating vector_a_, b_, and t_, 
	///		where vector_a_ is all starting points, b_ the target point(s), and t_ the interpolation weighting(s), in the provided index range. 
	///		Indices outside of the provided index range will be copies of the respective indices in vector_a_.
	/// </para>
	/// <para> If b_ is an EmuMath Vector: Individual output indices will use the respective index in b_ as the target point of interpolation. </para>
	/// <para> If t_ is an EmuMath Vector: Individual output indices will use the respective index in t_ as the interpolation weighting. </para>
	/// <para> If a valid argument type is *not* an EmuMath Vector: All output indices will use that value in every interpolation. </para>
	/// </summary>
	/// <param name="vector_a_">EmuMath Vector to copy, and used as the starting point of interpolations. a in the equation `a + ((b - a) * t)`.</param>
	/// <param name="b_">Scalar or EmuMath Vector used as the target point of interpolations. b in the equation `a + ((b - a) * t)`.</param>
	/// <param name="t_">Scalar or EmuMath Vector used as the weighting of interpolations. t in the equation `a + ((b - a) * t)`.</param>
	/// <returns>
	///		Copy of vector_a_, with results of linearly interpolating the provided arguments as described in the provided index range,
	///		stored as the desired output EmuMath Vector type.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ASize_, typename AT_, typename B_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_lerp_range(const EmuMath::NewVector<ASize_, AT_>& vector_a_, B_&& b_, T_&& t_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_lerp, OutSize_, OutT_, ASize_, AT_, BeginIndex_, EndIndex_)
		(
			vector_a_,
			vector_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ASize_, typename AT_, typename B_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<ASize_, OutT_> new_vector_lerp_range(const EmuMath::NewVector<ASize_, AT_>& vector_a_, B_&& b_, T_&& t_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_lerp, ASize_, OutT_, ASize_, AT_, BeginIndex_, EndIndex_)
		(
			vector_a_,
			vector_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ASize_, typename AT_, typename B_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<ASize_, AT_>::value_type_uq> new_vector_lerp_range
	(
		const EmuMath::NewVector<ASize_, AT_>& vector_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_value_uq = typename EmuMath::NewVector<ASize_, AT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_lerp, OutSize_, a_value_uq, ASize_, AT_, BeginIndex_, EndIndex_)
		(
			vector_a_,
			vector_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ASize_, typename AT_, typename B_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<ASize_, typename EmuMath::NewVector<ASize_, AT_>::value_type_uq> new_vector_lerp_range
	(
		const EmuMath::NewVector<ASize_, AT_>& vector_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_value_uq = typename EmuMath::NewVector<ASize_, AT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE(EmuCore::do_lerp, ASize_, a_value_uq, ASize_, AT_, BeginIndex_, EndIndex_)
		(
			vector_a_,
			vector_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	/// <summary>
	/// <para>
	///		Outputs to the provided out_vector_ using the results of linearly interpolating vector_a_, b_, and t_, 
	///		where vector_a_ is all starting points, b_ the target point(s), and t_ the interpolation weighting(s), in the provided index range. 
	///		Indices outside of the provided index range will be copies of the respective indices in vector_a_.
	/// </para>
	/// <para> If b_ is an EmuMath Vector: Individual output indices will use the respective index in b_ as the target point of interpolation. </para>
	/// <para> If t_ is an EmuMath Vector: Individual output indices will use the respective index in t_ as the interpolation weighting. </para>
	/// <para> If a valid argument type is *not* an EmuMath Vector: All output indices will use that value in every interpolation. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="vector_a_">EmuMath Vector to copy, and used as the starting point of interpolations. a in the equation `a + ((b - a) * t)`.</param>
	/// <param name="b_">Scalar or EmuMath Vector used as the target point of interpolations. b in the equation `a + ((b - a) * t)`.</param>
	/// <param name="t_">Scalar or EmuMath Vector used as the weighting of interpolations. t in the equation `a + ((b - a) * t)`.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ASize_, typename AT_, typename B_, typename T_, std::size_t OutSize_, typename OutT_>
	[[nodiscard]] constexpr inline void new_vector_lerp_range
	(
		EmuMath::NewVector<OutSize_, OutT_>& out_vector_,
		const EmuMath::NewVector<ASize_, AT_>& vector_a_,
		B_&& b_,
		T_&& t_
	)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE(EmuCore::do_lerp, OutSize_, OutT_, ASize_, AT_, BeginIndex_, EndIndex_)
		(			
			out_vector_,
			vector_a_,
			vector_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	/// <summary>
	/// <para>
	///		Outputs an EmuMath Vector of the provided OutSize and OutT_, containing the results of linearly interpolating vector_a_, b_, and t_, 
	///		where vector_a_ is all starting points, b_ the target point(s), and t_ the interpolation weighting(s), in the provided index range. 
	///		Indices outside of the provided index range will be default-constructed.
	/// </para>
	/// <para> If b_ is an EmuMath Vector: Individual output indices will use the respective arg index in b_ as the target point of interpolation. </para>
	/// <para> If t_ is an EmuMath Vector: Individual output indices will use the respective arg index in t_ as the interpolation weighting. </para>
	/// <para> If a valid argument type is *not* an EmuMath Vector: All arg indices will use that value in every interpolation. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing interpolation results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing interpolation results to the output Vector. </para>
	/// <para>
	///		LerpBegin_: Index within vector_a_ at which to start performing linear interpolations. This will increment by 1 for each interpolation, 
	///		and will also be used for accessing b_ and t_ if they are EmuMath Vectors.
	/// </para>
	/// </summary>
	/// <param name="vector_a_">EmuMath Vector to copy, and used as the starting point of interpolations. a in the equation `a + ((b - a) * t)`.</param>
	/// <param name="b_">Scalar or EmuMath Vector used as the target point of interpolations. b in the equation `a + ((b - a) * t)`.</param>
	/// <param name="t_">Scalar or EmuMath Vector used as the weighting of interpolations. t in the equation `a + ((b - a) * t)`.</param>
	/// <returns>
	///		EmuMath Vector of the desired type containing the results of linearly interpolating the provided arguments as described in the provided index range,
	///		with indices outside of the range default-constructed.
	/// </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t LerpBegin_, typename AT_, std::size_t ASize_, typename B_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_lerp_range_no_copy(const EmuMath::NewVector<ASize_, AT_>& vector_a_, B_&& b_, T_&& t_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_lerp, OutSize_, OutT_, OutBegin_, OutEnd_, LerpBegin_)
		(
			vector_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t LerpBegin_, typename AT_, std::size_t ASize_, typename B_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<ASize_, OutT_> new_vector_lerp_range_no_copy(const EmuMath::NewVector<ASize_, AT_>& vector_a_, B_&& b_, T_&& t_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_lerp, ASize_, OutT_, OutBegin_, OutEnd_, LerpBegin_)
		(
			vector_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t LerpBegin_, typename AT_, std::size_t ASize_, typename B_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<ASize_, AT_>::value_type_uq> new_vector_lerp_range_no_copy
	(
		const EmuMath::NewVector<ASize_, AT_>& vector_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_value_uq = typename EmuMath::NewVector<ASize_, AT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_lerp, OutSize_, a_value_uq, OutBegin_, OutEnd_, LerpBegin_)
		(
			vector_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t LerpBegin_, typename AT_, std::size_t ASize_, typename B_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<ASize_, typename EmuMath::NewVector<ASize_, AT_>::value_type_uq> new_vector_lerp_range_no_copy
	(
		const EmuMath::NewVector<ASize_, AT_>& vector_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_value_uq = typename EmuMath::NewVector<ASize_, AT_>::value_type_uq;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE(EmuCore::do_lerp, ASize_, a_value_uq, OutBegin_, OutEnd_, LerpBegin_)
		(
			vector_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	/// <summary>
	/// <para>
	///		Outputs to the provided out_vector_ using the results of linearly interpolating vector_a_, b_, and t_, 
	///		where vector_a_ is all starting points, b_ the target point(s), and t_ the interpolation weighting(s), in the provided index range. 
	///		Indices outside of the provided index range will not be modified.
	/// </para>
	/// <para> If b_ is an EmuMath Vector: Individual output indices will use the respective arg index in b_ as the target point of interpolation. </para>
	/// <para> If t_ is an EmuMath Vector: Individual output indices will use the respective arg index in t_ as the interpolation weighting. </para>
	/// <para> If a valid argument type is *not* an EmuMath Vector: All arg indices will use that value in every interpolation. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing interpolation results to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing interpolation results to the output Vector. </para>
	/// <para>
	///		LerpBegin_: Index within vector_a_ at which to start performing linear interpolations. This will increment by 1 for each interpolation, 
	///		and will also be used for accessing b_ and t_ if they are EmuMath Vectors.
	/// </para>
	/// </summary>
	/// <param name="vector_a_">EmuMath Vector to copy, and used as the starting point of interpolations. a in the equation `a + ((b - a) * t)`.</param>
	/// <param name="b_">Scalar or EmuMath Vector used as the target point of interpolations. b in the equation `a + ((b - a) * t)`.</param>
	/// <param name="t_">Scalar or EmuMath Vector used as the weighting of interpolations. t in the equation `a + ((b - a) * t)`.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t LerpBegin_, typename AT_, std::size_t ASize_, typename B_, typename T_, std::size_t OutSize_, typename OutT_>
	[[nodiscard]] constexpr inline void new_vector_lerp_range_no_copy
	(
		EmuMath::NewVector<OutSize_, OutT_>& out_vector_,
		const EmuMath::NewVector<ASize_, AT_>& vector_a_,
		B_&& b_,
		T_&& t_
	)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE(EmuCore::do_lerp, OutSize_, OutT_, OutBegin_, OutEnd_, LerpBegin_)
		(
			out_vector_,
			vector_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
#pragma endregion

#pragma region MIN_FUNCS
	/// <summary>
	/// <para> Finds the lowest value within the passed EmuMath Vector. </para>
	/// </summary>
	/// <param name="in_vector_">EmuMath Vector to find the lowest value of.</param>
	/// <returns>Lowest value within in_vector_, represented as the provided Out_ type (defaults to in_vector_'s value_type_uq).</returns>
	template<typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ new_vector_min(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		return _vector_underlying::_vector_min<Out_>(in_vector_);
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::value_type_uq new_vector_min(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		return _vector_underlying::_vector_min<typename EmuMath::NewVector<Size_, T_>::value_type_uq>(in_vector_);
	}

	/// <summary>
	/// <para> Finds the lowest value within the passed EmuMath Vector, using only indices within the provided (theoretical) range. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading values from the input Vector. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading values from the input Vector. </para>
	/// </summary>
	/// <param name="in_vector_">EmuMath Vector to find the lowest value of.</param>
	/// <returns>Lowest value within in_vector_, represented as the provided Out_ type (defaults to in_vector_'s value_type_uq).</returns>
	template<typename Out_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ new_vector_min(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		return _vector_underlying::_vector_min<Out_, BeginIndex_, EndIndex_>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::value_type_uq new_vector_min(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		return _vector_underlying::_vector_min<typename EmuMath::NewVector<Size_, T_>::value_type_uq, BeginIndex_, EndIndex_>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a Vector containing the lowest element in each respective index between vector_a_ and b_. </para>
	/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in vector_a_ will be compared with b_ directly. </para>
	/// </summary>
	/// <param name="vector_a_">: EmuMath Vector appearing as the first argument in comparisons.</param>
	/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
	/// <returns>EmuMath Vector formed of the lowest values of vector_a_ and b_ as described.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_min(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, OutSize_, OutT_)(vector_a_, std::forward<B_>(b_));
	}

	template<typename OutT_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<SizeA_, OutT_> new_vector_min(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, SizeA_, OutT_)(vector_a_, std::forward<B_>(b_));
	}

	template<std::size_t OutSize_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>
	new_vector_min(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		// We use preferred_floating_point instead of value_type_uq by default so that comparisons between int and fp produce expected results
		// --- E.g. if the min is -2.2, and value_type_uq is int, we implicitly truncate the min to -2; use of preferred_floating_point erases this issue
		// ------ This also tackles the issue of signed-ness if value_type_uq is unsigned, but the min is negative.
		// --- This makes potentially invalidating conversions such as truncation and unsigned wrapping explicit, opt-in occurrences.
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, OutSize_, a_fp)(vector_a_, std::forward<B_>(b_));
	}

	template<typename TA_, typename B_, std::size_t SizeA_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<SizeA_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>
	new_vector_min(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, SizeA_, a_fp)(vector_a_, std::forward<B_>(b_));
	}

	/// <summary>
	/// <para> Outputs a Vector containing the lowest element in each respective index between vector_a_ and b_, via the provided out_vector_. </para>
	/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in vector_a_ will be compared with b_ directly. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_a_">: EmuMath Vector appearing as the first argument in comparisons.</param>
	/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
	template<std::size_t OutSize_, typename OutT_, typename TA_, typename B_, std::size_t SizeA_>
	constexpr inline void new_vector_min(EmuMath::NewVector<OutSize_, OutT_&> out_vector_, const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, OutSize_, OutT_)(out_vector_, vector_a_, std::forward<B_>(b_));
	}

	/// <summary>
	/// <para> Outputs a Vector containing the lowest element in each respective index between vector_a_ and b_ within the provided range. </para>
	/// <para> Indices outside of the provided range will be copies of elements within the respective index of vector_a_. </para>
	/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in vector_a_ will be compared with b_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start determining and copying min values. </para>
	/// <para> EndIndex_: Exclusive index at which to stop determining and copying min values. </para>
	/// </summary>
	/// <param name="vector_a_">: EmuMath Vector appearing as the first argument in comparisons.</param>
	/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
	/// <returns>EmuMath Vector formed of the lowest values of vector_a_ and b_ as described in the provided range, and copies oh vector_a_ outside of said range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename TA_, std::size_t SizeA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_min_range(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, OutSize_, OutT_, SizeA_, TA_, BeginIndex_, EndIndex_)
		(
			vector_a_,
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename TA_, std::size_t SizeA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<SizeA_, OutT_> new_vector_min_range(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, SizeA_, OutT_, SizeA_, TA_, BeginIndex_, EndIndex_)
		(
			vector_a_,
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, typename TA_, std::size_t SizeA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>
	new_vector_min_range(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, OutSize_, a_fp, SizeA_, TA_, BeginIndex_, EndIndex_)
		(
			vector_a_,
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename TA_, std::size_t SizeA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<SizeA_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>
	new_vector_min_range(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, SizeA_, a_fp, SizeA_, TA_, BeginIndex_, EndIndex_)
		(
			vector_a_,
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	/// <summary>
	/// <para> Outputs a Vector containing the lowest element in each respective index between vector_a_ and b_ within the provided range, via the passed out_vector_. </para>
	/// <para> Indices outside of the provided range will be copies of elements within the respective index of vector_a_. </para>
	/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in vector_a_ will be compared with b_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start determining and copying min values. </para>
	/// <para> EndIndex_: Exclusive index at which to stop determining and copying min values. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_a_">: EmuMath Vector appearing as the first argument in comparisons.</param>
	/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, std::size_t SizeA_, typename TA_, typename B_>
	constexpr inline void new_vector_min_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, OutSize_, OutT_, SizeA_, TA_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_a_,
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	/// <summary>
	/// <para> Outputs a Vector with indices in the provided index range containing the lowest values of indices of vector_a_ and b_, starting from index MinBegin_. </para>
	/// <para> Indices outside of the provided range will be default-constructed. </para>
	/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in vector_a_ will be compared with b_ directly. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing min values to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing min values to the output Vector. </para>
	/// <para> MinBegin_: Inclusive index at which to start reading values from vector_a_ (and b_ if it is an EmuMath Vector) for operations. Incremented per iteration. </para>
	/// </summary>
	/// <param name="vector_a_">: EmuMath Vector appearing as the first argument in comparisons.</param>
	/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
	/// <returns>EmuMath Vector containing min results in the provided range, and default-constructed elements elsewhere.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MinBegin_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_min_range_no_copy(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, OutSize_, OutT_, OutBegin_, OutEnd_, MinBegin_)
		(
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MinBegin_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<SizeA_, OutT_> new_vector_min_range_no_copy(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, SizeA_, OutT_, OutBegin_, OutEnd_, MinBegin_)
		(
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MinBegin_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>
	new_vector_min_range_no_copy(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, OutSize_, a_fp, OutBegin_, OutEnd_, MinBegin_)
		(
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MinBegin_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<SizeA_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>
	new_vector_min_range_no_copy(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, SizeA_, a_fp, OutBegin_, OutEnd_, MinBegin_)
		(
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	/// <summary>
	/// <para>
	///		Outputs a Vector with indices in the provided index range containing the lowest values of indices of vector_a_ and b_, starting from index MinBegin_, 
	///		via the passed out_vector_.
	/// </para>
	/// <para> Indices outside of the provided range will not be modified. </para>
	/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in vector_a_ will be compared with b_ directly. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing min values to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing min values to the output Vector. </para>
	/// <para> MinBegin_: Inclusive index at which to start reading values from vector_a_ (and b_ if it is an EmuMath Vector) for operations. Incremented per iteration. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_a_">: EmuMath Vector appearing as the first argument in comparisons.</param>
	/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MinBegin_, std::size_t OutSize_, typename OutT_, std::size_t SizeA_, typename TA_, typename B_>
	constexpr inline void new_vector_min_range_no_copy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE_APPEND_OUT(EmuCore::do_min, false, OutSize_, OutT_, OutBegin_, OutEnd_, MinBegin_)
		(
			out_vector_,
			vector_a_,
			std::forward<B_>(b_)
		);
	}
#pragma endregion

#pragma region MAX_FUNCS
	/// <summary>
	/// <para> Finds the greatest value within the passed EmuMath Vector. </para>
	/// </summary>
	/// <param name="in_vector_">EmuMath Vector to find the greatest value of.</param>
	/// <returns>Greatest value within in_vector_, represented as the provided Out_ type (defaults to in_vector_'s value_type_uq).</returns>
	template<typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ new_vector_max(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		return _vector_underlying::_vector_max<Out_>(in_vector_);
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::value_type_uq new_vector_max(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		return _vector_underlying::_vector_max<typename EmuMath::NewVector<Size_, T_>::value_type_uq>(in_vector_);
	}

	/// <summary>
	/// <para> Finds the greatest value within the passed EmuMath Vector, using only indices within the provided (theoretical) range. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading values from the input Vector. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading values from the input Vector. </para>
	/// </summary>
	/// <param name="in_vector_">EmuMath Vector to find the greatest value of.</param>
	/// <returns>Greatest value in the provided index range within in_vector_, represented as the provided Out_ type (defaults to in_vector_'s value_type_uq).</returns>
	template<typename Out_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ new_vector_max(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		return _vector_underlying::_vector_max<Out_, BeginIndex_, EndIndex_>(in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::value_type_uq new_vector_max(const EmuMath::NewVector<Size_, T_>& in_vector_)
	{
		return _vector_underlying::_vector_max<typename EmuMath::NewVector<Size_, T_>::value_type_uq, BeginIndex_, EndIndex_>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a Vector containing the greatest element in each respective index between vector_a_ and b_. </para>
	/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in vector_a_ will be compared with b_ directly. </para>
	/// </summary>
	/// <param name="vector_a_">: EmuMath Vector appearing as the first argument in comparisons.</param>
	/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
	/// <returns>EmuMath Vector formed of the greatest values of vector_a_ and b_ as described.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_max(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, OutSize_, OutT_)(vector_a_, std::forward<B_>(b_));
	}

	template<typename OutT_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<SizeA_, OutT_> new_vector_max(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, SizeA_, OutT_)(vector_a_, std::forward<B_>(b_));
	}

	template<std::size_t OutSize_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>
	new_vector_max(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, OutSize_, a_fp)(vector_a_, std::forward<B_>(b_));
	}

	template<typename TA_, typename B_, std::size_t SizeA_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<SizeA_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>
	new_vector_max(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return EMU_MATH_VECTOR_MUTATE_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, SizeA_, a_fp)(vector_a_, std::forward<B_>(b_));
	}

	/// <summary>
	/// <para> Outputs a Vector containing the greatest element in each respective index between vector_a_ and b_, via the provided out_vector_. </para>
	/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in vector_a_ will be compared with b_ directly. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_a_">: EmuMath Vector appearing as the first argument in comparisons.</param>
	/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
	template<std::size_t OutSize_, typename OutT_, typename TA_, typename B_, std::size_t SizeA_>
	constexpr inline void new_vector_max(EmuMath::NewVector<OutSize_, OutT_&> out_vector_, const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, OutSize_, OutT_)(out_vector_, vector_a_, std::forward<B_>(b_));
	}

	/// <summary>
	/// <para> Outputs a Vector containing the greatest element in each respective index between vector_a_ and b_ within the provided range. </para>
	/// <para> Indices outside of the provided range will be copies of elements within the respective index of vector_a_. </para>
	/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in vector_a_ will be compared with b_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start determining and copying min values. </para>
	/// <para> EndIndex_: Exclusive index at which to stop determining and copying min values. </para>
	/// </summary>
	/// <param name="vector_a_">: EmuMath Vector appearing as the first argument in comparisons.</param>
	/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
	/// <returns>EmuMath Vector formed of the greatest values of vector_a_ and b_ as described in the provided range, and copies oh vector_a_ outside of said range.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename TA_, std::size_t SizeA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_max_range(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, OutSize_, OutT_, SizeA_, TA_, BeginIndex_, EndIndex_)
		(
			vector_a_,
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename TA_, std::size_t SizeA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<SizeA_, OutT_> new_vector_max_range(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, SizeA_, OutT_, SizeA_, TA_, BeginIndex_, EndIndex_)
		(
			vector_a_,
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, typename TA_, std::size_t SizeA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>
	new_vector_max_range(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, OutSize_, a_fp, SizeA_, TA_, BeginIndex_, EndIndex_)
		(
			vector_a_,
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename TA_, std::size_t SizeA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<SizeA_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>
	new_vector_max_range(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return EMU_MATH_VECTOR_MUTATE_RANGE_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, SizeA_, a_fp, SizeA_, TA_, BeginIndex_, EndIndex_)
		(
			vector_a_,
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	/// <summary>
	/// <para> Outputs a Vector containing the greatest element in each respective index between vector_a_ and b_ within the provided range, via the passed out_vector_. </para>
	/// <para> Indices outside of the provided range will be copies of elements within the respective index of vector_a_. </para>
	/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in vector_a_ will be compared with b_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start determining and copying min values. </para>
	/// <para> EndIndex_: Exclusive index at which to stop determining and copying min values. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_a_">: EmuMath Vector appearing as the first argument in comparisons.</param>
	/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, std::size_t SizeA_, typename TA_, typename B_>
	constexpr inline void new_vector_max_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, OutSize_, OutT_, SizeA_, TA_, BeginIndex_, EndIndex_)
		(
			out_vector_,
			vector_a_,
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	/// <summary>
	/// <para> Outputs a Vector with indices in the provided index range containing the greatest values of indices of vector_a_ and b_, starting from index MinBegin_. </para>
	/// <para> Indices outside of the provided range will be default-constructed. </para>
	/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in vector_a_ will be compared with b_ directly. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing min values to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing min values to the output Vector. </para>
	/// <para> MaxBegin_: Inclusive index at which to start reading values from vector_a_ (and b_ if it is an EmuMath Vector) for operations. Incremented per iteration. </para>
	/// </summary>
	/// <param name="vector_a_">: EmuMath Vector appearing as the first argument in comparisons.</param>
	/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
	/// <returns>EmuMath Vector containing max results in the provided range, and default-constructed elements elsewhere.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MaxBegin_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_max_range_no_copy(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, OutSize_, OutT_, OutBegin_, OutEnd_, MaxBegin_)
		(
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MaxBegin_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<SizeA_, OutT_> new_vector_max_range_no_copy(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, SizeA_, OutT_, OutBegin_, OutEnd_, MaxBegin_)
		(
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MaxBegin_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>
	new_vector_max_range_no_copy(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, OutSize_, a_fp, OutBegin_, OutEnd_, MaxBegin_)
		(
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MaxBegin_, std::size_t SizeA_, typename TA_, typename B_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<SizeA_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>
	new_vector_max_range_no_copy(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		using a_fp = typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point;
		return EMU_MATH_VECTOR_MUTATE_RANGE_NO_COPY_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, SizeA_, a_fp, OutBegin_, OutEnd_, MaxBegin_)
		(
			vector_a_,
			std::forward<B_>(b_)
		);
	}

	/// <summary>
	/// <para>
	///		Outputs a Vector with indices in the provided index range containing the greatest values of indices of vector_a_ and b_, starting from index MinBegin_, 
	///		via the passed out_vector_.
	/// </para>
	/// <para> Indices outside of the provided range will not be modified. </para>
	/// <para> If B_ is an EmuMath Vector: Respective indices will be compared. Otherwise, all indices in vector_a_ will be compared with b_ directly. </para>
	/// <para> OutBegin_: Inclusive index at which to start writing min values to the output Vector. </para>
	/// <para> OutEnd_: Exclusive index at which to stop writing min values to the output Vector. </para>
	/// <para> MaxBegin_: Inclusive index at which to start reading values from vector_a_ (and b_ if it is an EmuMath Vector) for operations. Incremented per iteration. </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to output to.</param>
	/// <param name="vector_a_">: EmuMath Vector appearing as the first argument in comparisons.</param>
	/// <param name="b_">: Scalar or EmuMath Vector appearing as the second argument in comparisons.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t MaxBegin_, std::size_t OutSize_, typename OutT_, std::size_t SizeA_, typename TA_, typename B_>
	constexpr inline void new_vector_max_range_no_copy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<SizeA_, TA_>& vector_a_, B_&& b_)
	{
		EMU_MATH_VECTOR_MUTATE_REF_RANGE_NO_COPY_TEMPLATE_APPEND_OUT(EmuCore::do_max, false, OutSize_, OutT_, OutBegin_, OutEnd_, MaxBegin_)
		(
			out_vector_,
			vector_a_,
			std::forward<B_>(b_)
		);
	}
#pragma endregion
}

#endif
