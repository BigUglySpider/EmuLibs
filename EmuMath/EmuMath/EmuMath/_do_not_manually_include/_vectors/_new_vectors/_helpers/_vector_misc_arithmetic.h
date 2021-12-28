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
}

#endif
