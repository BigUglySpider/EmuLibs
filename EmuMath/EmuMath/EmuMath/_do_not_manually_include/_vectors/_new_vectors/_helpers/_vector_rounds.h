#ifndef EMU_MATH_NEW_VECTOR_ROUNDS_H_INC_
#define EMU_MATH_NEW_VECTOR_ROUNDS_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../../EmuCore/Functors/Arithmetic.h"

namespace EmuMath::Helpers
{
#pragma region FLOOR_FUNCS
	/// <summary>
	/// <para> Outputs a floored form of the provided EmuMath Vector, with the output Vector using the provided OutSize_ and OutT_ template arguments. </para>
	/// <para> For a guarantee to perform rounds as constexpr if possible, use `vector_floor_constexpr` instead. </para>
	/// <para> OutSize_: Optional argument used as the Size_ argument for the output EmuMath Vector type. Defaults to the input Vector's Size_. </para>
	/// <para> OutT_: Optional argument used as the T_ argument for the output EmuMath Vector type. Defaults to the input Vector's value_type_uq. </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to output the floored form of.</param>
	/// <returns>Form of in_vector_ rounded toward negative infinity, as an EmuMath Vector type formed from the provided OutSize_ and OutT_ arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_floor(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_floor<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<typename OutT_, std::size_t Size_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_floor(const EmuMath::NewVector<Size_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_floor<typename EmuMath::NewVector<Size_, InT_>::value_type_uq>,
			EmuMath::NewVector<Size_, OutT_>,
			0,
			EmuMath::NewVector<Size_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_floor
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_floor<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			0,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>::size,
			0
		>(in_vector_);
	}
	template<typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_floor
	(
		const EmuMath::NewVector<Size_, T_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_floor<typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			0,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>::size,
			0
		>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a floored form of the provided in_vector_ to the provided out_vector_. </para>
	/// <para> For a guarantee to perform rounds as constexpr if possible, use `vector_floor_constexpr` instead. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="in_vector_">EmuMath Vector to output the floored form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_floor(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		_vector_underlying::_vector_mutate_no_func_passed
		<
			EmuCore::do_floor<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(out_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a floored form of the provided EmuMath Vector, with the output Vector using the provided OutSize_ and OutT_ template arguments. </para>
	/// <para>
	///		Provides a guarantee to be constexpr if possible, but this may make sacrifices to areas such as performance.
	///		For calls guaranteed to be at runtime, it is recommended to use `vector_floor` instead.
	/// </para>
	/// <para> OutSize_: Optional argument used as the Size_ argument for the output EmuMath Vector type. Defaults to the input Vector's Size_. </para>
	/// <para> OutT_: Optional argument used as the T_ argument for the output EmuMath Vector type. Defaults to the input Vector's value_type_uq. </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to output the floored form of.</param>
	/// <returns>Form of in_vector_ rounded toward positive infinity, as an EmuMath Vector type formed from the provided OutSize_ and OutT_ arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_floor_constexpr(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_floor_constexpr<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<typename OutT_, std::size_t Size_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_floor_constexpr(const EmuMath::NewVector<Size_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_floor_constexpr<typename EmuMath::NewVector<Size_, InT_>::value_type_uq>,
			EmuMath::NewVector<Size_, OutT_>,
			0,
			EmuMath::NewVector<Size_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_floor_constexpr
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_floor_constexpr<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			0,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>::size,
			0
		>(in_vector_);
	}
	template<typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_floor_constexpr
	(
		const EmuMath::NewVector<Size_, T_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_floor_constexpr<typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			0,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>::size,
			0
		>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a floored form of the provided in_vector_ to the provided out_vector_. </para>
	/// <para>
	///		Provides a guarantee to be constexpr if possible, but this may make sacrifices to areas such as performance.
	///		For calls guaranteed to be at runtime, it is recommended to use `vector_floor` instead.
	/// </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="in_vector_">EmuMath Vector to output the floored form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_floor_constexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		_vector_underlying::_vector_mutate_no_func_passed
		<
			EmuCore::do_floor_constexpr<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(out_vector_, in_vector_);
	}
#pragma endregion

#pragma region CEIL_FUNCS
	/// <summary>
	/// <para> Outputs a ceiled form of the provided EmuMath Vector, with the output Vector using the provided OutSize_ and OutT_ template arguments. </para>
	/// <para> For a guarantee to perform rounds as constexpr if possible, use `vector_ceil_constexpr` instead. </para>
	/// <para> OutSize_: Optional argument used as the Size_ argument for the output EmuMath Vector type. Defaults to the input Vector's Size_. </para>
	/// <para> OutT_: Optional argument used as the T_ argument for the output EmuMath Vector type. Defaults to the input Vector's value_type_uq. </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to output the ceiled form of.</param>
	/// <returns>Form of in_vector_ rounded toward positive infinity, as an EmuMath Vector type formed from the provided OutSize_ and OutT_ arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_ceil(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_ceil<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<typename OutT_, std::size_t Size_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_ceil(const EmuMath::NewVector<Size_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_ceil<typename EmuMath::NewVector<Size_, InT_>::value_type_uq>,
			EmuMath::NewVector<Size_, OutT_>,
			0,
			EmuMath::NewVector<Size_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_ceil
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_ceil<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			0,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>::size,
			0
		>(in_vector_);
	}
	template<typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_ceil
	(
		const EmuMath::NewVector<Size_, T_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_ceil<typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			0,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>::size,
			0
		>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a ceiled form of the provided in_vector_ to the provided out_vector_. </para>
	/// <para> For a guarantee to perform rounds as constexpr if possible, use `vector_ceil_constexpr` instead. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="in_vector_">EmuMath Vector to output the ceiled form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_ceil(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		_vector_underlying::_vector_mutate_no_func_passed
		<
			EmuCore::do_ceil<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(out_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a ceiled form of the provided EmuMath Vector, with the output Vector using the provided OutSize_ and OutT_ template arguments. </para>
	/// <para>
	///		Provides a guarantee to be constexpr if possible, but this may make sacrifices to areas such as performance.
	///		For calls guaranteed to be at runtime, it is recommended to use `vector_ceil` instead.
	/// </para>
	/// <para> OutSize_: Optional argument used as the Size_ argument for the output EmuMath Vector type. Defaults to the input Vector's Size_. </para>
	/// <para> OutT_: Optional argument used as the T_ argument for the output EmuMath Vector type. Defaults to the input Vector's value_type_uq. </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to output the ceiled form of.</param>
	/// <returns>Form of in_vector_ rounded toward positive infinity, as an EmuMath Vector type formed from the provided OutSize_ and OutT_ arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_ceil_constexpr(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_ceil_constexpr<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<typename OutT_, std::size_t Size_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_ceil_constexpr(const EmuMath::NewVector<Size_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_ceil_constexpr<typename EmuMath::NewVector<Size_, InT_>::value_type_uq>,
			EmuMath::NewVector<Size_, OutT_>,
			0,
			EmuMath::NewVector<Size_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_ceil_constexpr
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_ceil_constexpr<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			0,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>::size,
			0
		>(in_vector_);
	}
	template<typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_ceil_constexpr
	(
		const EmuMath::NewVector<Size_, T_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_ceil_constexpr<typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			0,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>::size,
			0
		>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a ceiled form of the provided in_vector_ to the provided out_vector_. </para>
	/// <para>
	///		Provides a guarantee to be constexpr if possible, but this may make sacrifices to areas such as performance.
	///		For calls guaranteed to be at runtime, it is recommended to use `vector_ceil` instead.
	/// </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="in_vector_">EmuMath Vector to output the ceiled form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_ceil_constexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		_vector_underlying::_vector_mutate_no_func_passed
		<
			EmuCore::do_ceil_constexpr<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(out_vector_, in_vector_);
	}
#pragma endregion

#pragma region TRUNC_FUNCS
	/// <summary>
	/// <para> Outputs a truncated form of the provided EmuMath Vector, with the output Vector using the provided OutSize_ and OutT_ template arguments. </para>
	/// <para> For a guarantee to perform rounds as constexpr if possible, use `vector_trunc_constexpr` instead. </para>
	/// <para> OutSize_: Optional argument used as the Size_ argument for the output EmuMath Vector type. Defaults to the input Vector's Size_. </para>
	/// <para> OutT_: Optional argument used as the T_ argument for the output EmuMath Vector type. Defaults to the input Vector's value_type_uq. </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to output the truncated form of.</param>
	/// <returns>Form of in_vector_ rounded toward 0, as an EmuMath Vector type formed from the provided OutSize_ and OutT_ arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_trunc(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_trunc<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<typename OutT_, std::size_t Size_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_trunc(const EmuMath::NewVector<Size_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_trunc<typename EmuMath::NewVector<Size_, InT_>::value_type_uq>,
			EmuMath::NewVector<Size_, OutT_>,
			0,
			EmuMath::NewVector<Size_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_trunc
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_trunc<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			0,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>::size,
			0
		>(in_vector_);
	}
	template<typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_trunc
	(
		const EmuMath::NewVector<Size_, T_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_trunc<typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			0,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>::size,
			0
		>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a truncated form of the provided in_vector_ to the provided out_vector_. </para>
	/// <para> For a guarantee to perform rounds as constexpr if possible, use `vector_trunc_constexpr` instead. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="in_vector_">EmuMath Vector to output the truncated form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_trunc(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		_vector_underlying::_vector_mutate_no_func_passed
		<
			EmuCore::do_trunc<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(out_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a truncated form of the provided EmuMath Vector, with the output Vector using the provided OutSize_ and OutT_ template arguments. </para>
	/// <para>
	///		Provides a guarantee to be constexpr if possible, but this may make sacrifices to areas such as performance.
	///		For calls guaranteed to be at runtime, it is recommended to use `vector_trunc` instead.
	/// </para>
	/// <para> OutSize_: Optional argument used as the Size_ argument for the output EmuMath Vector type. Defaults to the input Vector's Size_. </para>
	/// <para> OutT_: Optional argument used as the T_ argument for the output EmuMath Vector type. Defaults to the input Vector's value_type_uq. </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to output the truncated form of.</param>
	/// <returns>Form of in_vector_ rounded toward 0, as an EmuMath Vector type formed from the provided OutSize_ and OutT_ arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_trunc_constexpr(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_trunc_constexpr<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<typename OutT_, std::size_t Size_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_trunc_constexpr(const EmuMath::NewVector<Size_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_trunc_constexpr<typename EmuMath::NewVector<Size_, InT_>::value_type_uq>,
			EmuMath::NewVector<Size_, OutT_>,
			0,
			EmuMath::NewVector<Size_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_trunc_constexpr
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_trunc_constexpr<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			0,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>::size,
			0
		>(in_vector_);
	}
	template<typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_trunc_constexpr
	(
		const EmuMath::NewVector<Size_, T_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_trunc_constexpr<typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			0,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>::size,
			0
		>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a truncated form of the provided in_vector_ to the provided out_vector_. </para>
	/// <para>
	///		Provides a guarantee to be constexpr if possible, but this may make sacrifices to areas such as performance.
	///		For calls guaranteed to be at runtime, it is recommended to use `vector_trunc` instead.
	/// </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="in_vector_">EmuMath Vector to output the truncated form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_trunc_constexpr(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		_vector_underlying::_vector_mutate_no_func_passed
		<
			EmuCore::do_trunc_constexpr<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(out_vector_, in_vector_);
	}
#pragma endregion

#pragma region ABS_FUNCS
	/// <summary>
	/// <para> Outputs an absolute form of the provided EmuMath Vector, with the output Vector using the provided OutSize_ and OutT_ template arguments. </para>
	/// <para> OutSize_: Optional argument used as the Size_ argument for the output EmuMath Vector type. Defaults to the input Vector's Size_. </para>
	/// <para> OutT_: Optional argument used as the T_ argument for the output EmuMath Vector type. Defaults to the input Vector's value_type_uq. </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to output the absolute form of.</param>
	/// <returns>Absolute form of in_vector_, (i.e. { 1, -2, 0 } -> { 1, 2, 0 }) as an EmuMath Vector type formed from the provided OutSize_ and OutT_ arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_abs(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_abs<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<typename OutT_, std::size_t Size_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_abs(const EmuMath::NewVector<Size_, InT_>& in_vector_)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_abs<typename EmuMath::NewVector<Size_, InT_>::value_type_uq>,
			EmuMath::NewVector<Size_, OutT_>,
			0,
			EmuMath::NewVector<Size_, OutT_>::size,
			0
		>(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq> new_vector_abs
	(
		const EmuMath::NewVector<InSize_, InT_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_abs<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			0,
			EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>::size,
			0
		>(in_vector_);
	}
	template<typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_abs
	(
		const EmuMath::NewVector<Size_, T_>& in_vector_
	)
	{
		return _vector_underlying::_vector_mutate_args_only
		<
			EmuCore::do_abs<typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>,
			0,
			EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>::size,
			0
		>(in_vector_);
	}

	/// <summary>
	/// <para> Outputs an absolute form of the provided in_vector_ to the provided out_vector_. </para>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="in_vector_">EmuMath Vector to output the absolute form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_abs(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		_vector_underlying::_vector_mutate_no_func_passed
		<
			EmuCore::do_abs<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>,
			EmuMath::NewVector<OutSize_, OutT_>,
			0,
			EmuMath::NewVector<OutSize_, OutT_>::size,
			0
		>(out_vector_, in_vector_);
	}
#pragma endregion
}

#endif
