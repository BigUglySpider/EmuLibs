#ifndef EMU_MATH_VECTOR_CMP_H_INC_
#define EMU_MATH_VECTOR_CMP_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../EmuCore/Functors/Comparators.h"

// CONTAINS:
// --- cmp_all
// --- cmp_any
// --- cmp_near
// --- cmp_all_near
// --- cmp_any_near
// --- cmp_not_near
// --- cmp_all_not_near
// --- cmp_any_not_near
// --- cmp_equal
// --- cmp_all_equal
// --- cmp_any_equal
// --- cmp_not_equal
// --- cmp_all_not_equal
// --- cmp_any_not_equal
// --- cmp_greater
// --- cmp_all_greater
// --- cmp_any_greater
// --- cmp_less
// --- cmp_all_less
// --- cmp_any_less
// --- cmp_greater_equal
// --- cmp_all_greater_equal
// --- cmp_any_greater_equal
// --- cmp_less_equal
// --- cmp_all_less_equal
// --- cmp_any_less_equal

namespace EmuMath::Helpers
{
#pragma region GENERIC_CMP_ALL_FUNCS
	/// <summary>
	/// <para> Returns the boolean result of an EmuMath Vector comparison using the provided Cmp_ function. </para>
	/// <para> Returns true only if all comparisons are true. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <param name="cmp_">: Invocable item to perform comparisons. Must return a type that may be interpreted as a bool when invoked with lhs_vector_ and rhs_ as described.</param>
	/// <returns>True if all comparisons with the provided Cmp_ are true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Cmp_, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_, Cmp_ cmp_)
	{
		using cmp_ref_ = std::add_lvalue_reference_t<Cmp_>;
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, IncludeNonContained_, cmp_ref_, Joiner_>(cmp_, Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	template<class Cmp_, bool IncludeNonContained_ = true, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, IncludeNonContained_, Cmp_, Joiner_>(Cmp_(), Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns the boolean result of an EmuMath Vector comparison using an automatically selected instantiation of the provided CmpTemplate_. </para>
	/// <para> CmpTemplate_ must be possible to instantiate with two type arguments. The provided type arguments will be based on the lhs_vector_ and rhs_ args. </para>
	/// <para> Returns true only if all comparisons are true. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons using the provided CmpTemplate_ are true, otherwise false.</returns>
	template<template<class...> class CmpTemplate_, bool IncludeNonContained_ = true, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, IncludeNonContained_, CmpTemplate_, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns the boolean result of an EmuMath Vector comparison using the provided Cmp_ function. </para>
	/// <para> Returns true only if all comparisons in the provided index range are true. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading values from Vectors for comparison. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading values from Vectors for comparison. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <param name="cmp_">: Invocable item to perform comparisons. Must return a type that may be interpreted as a bool when invoked with lhs_vector_ and rhs_ as described.</param>
	/// <returns>True if all comparisons with the provided Cmp_ within the provided index range are true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Cmp_, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_, Cmp_ cmp_)
	{
		using cmp_ref_ = std::add_lvalue_reference_t<Cmp_>;
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, BeginIndex_, EndIndex_, cmp_ref_, Joiner_>(cmp_, Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	template<class Cmp_, std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, BeginIndex_, EndIndex_, Cmp_, Joiner_>(Cmp_(), Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns the boolean result of an EmuMath Vector comparison using an automatically selected instantiation of the provided CmpTemplate_. </para>
	/// <para> CmpTemplate_ must be possible to instantiate with two type arguments. The provided type arguments will be based on the lhs_vector_ and rhs_ args. </para>
	/// <para> Returns true only if all comparisons in the provided index range are true. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading values from Vectors for comparison. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading values from Vectors for comparison. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons using the provided CmpTemplate_ within the provided index range are true, otherwise false.</returns>
	template<template<class...> class CmpTemplate_, std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, BeginIndex_, EndIndex_, CmpTemplate_, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion

#pragma region GENERIC_CMP_ANY_FUNCS
	/// <summary>
	/// <para> Returns the boolean result of an EmuMath Vector comparison using the provided Cmp_ function. </para>
	/// <para> Returns true if at least 1 comparison is true. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <param name="cmp_">: Invocable item to perform comparisons. Must return a type that may be interpreted as a bool when invoked with lhs_vector_ and rhs_ as described.</param>
	/// <returns>True if at least 1 comparison with the provided Cmp_ is true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Cmp_, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_, Cmp_ cmp_)
	{
		using cmp_ref_ = std::add_lvalue_reference_t<Cmp_>;
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, IncludeNonContained_, cmp_ref_, Joiner_>(cmp_, Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	template<class Cmp_, bool IncludeNonContained_ = true, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, IncludeNonContained_, Cmp_, Joiner_>(Cmp_(), Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns the boolean result of an EmuMath Vector comparison using an automatically selected instantiation of the provided CmpTemplate_. </para>
	/// <para> CmpTemplate_ must be possible to instantiate with two type arguments. The provided type arguments will be based on the lhs_vector_ and rhs_ args. </para>
	/// <para> Returns true if at least 1 comparison is true. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison using the provided CmpTemplate_ is true, otherwise false.</returns>
	template<template<class...> class CmpTemplate_, bool IncludeNonContained_ = true, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, IncludeNonContained_, CmpTemplate_, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns the boolean result of an EmuMath Vector comparison using the provided Cmp_ function. </para>
	/// <para> Returns true if at least 1 comparison is true. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading values from Vectors for comparison. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading values from Vectors for comparison. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <param name="cmp_">: Invocable item to perform comparisons. Must return a type that may be interpreted as a bool when invoked with lhs_vector_ and rhs_ as described.</param>
	/// <returns>True if at least 1 comparison with the provided Cmp_ within the provided index range is true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Cmp_, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_, Cmp_ cmp_)
	{
		using cmp_ref_ = std::add_lvalue_reference_t<Cmp_>;
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, cmp_ref_, Joiner_>(cmp_, Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	template<class Cmp_, std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, Cmp_, Joiner_>(Cmp_(), Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns the boolean result of an EmuMath Vector comparison using an automatically selected instantiation of the provided CmpTemplate_. </para>
	/// <para> CmpTemplate_ must be possible to instantiate with two type arguments. The provided type arguments will be based on the lhs_vector_ and rhs_ args. </para>
	/// <para> Returns true if at least 1 comparison is true. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading values from Vectors for comparison. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading values from Vectors for comparison. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison using the provided CmpTemplate_ within the provided index range is true, otherwise false.</returns>
	template<template<class...> class CmpTemplate_, std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, CmpTemplate_, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion

#pragma region CMP_NEAR_FUNCS
	/// <summary>
	/// <para> Adaptive near-equality comparison which changes behaviour based on the provided Rhs_ type, intended for safer floating-point equality checks. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Equivalent to vector_cmp_all_near. </para>
	/// <para> If Rhs_ is none of the above: Compares the magnitude of lhs_vector_ to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
	/// <para> IncludeNonContained_: Unused if Rhs_ is not an EmuMath Vector, otherwise used as in vector_cmp_all_near. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector appearing on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
	/// <returns>If Rhs_: is an EmuMath Vector: true if all comparisons are true, otherwise false. Otherwise, true if rhs_ is near-equal to lhs_vector_'s magnitude.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_near(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp_mag_if_rhs_scalar<true, IncludeNonContained_, EmuCore::do_cmp_near_equal, Joiner_>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Adaptive near-equality comparison which changes behaviour based on the provided Rhs_ type, intended for safer floating-point equality checks. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Equivalent to vector_cmp_all_near. </para>
	/// <para> If Rhs_ is none of the above: Compares the magnitude of lhs_vector_ to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for either performing comparisons or calculating magnitude. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for either performing comparisons or calculating magnitude. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector appearing on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
	/// <returns>
	///		If Rhs_: is an EmuMath Vector: true if all comparisons in the provided range are true, otherwise false. 
	///		Otherwise, true if rhs_ is near-equal to lhs_vector_'s magnitude when calculated using only indices within the provided range.
	/// </returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_near(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp_mag_if_rhs_scalar<true, BeginIndex_, EndIndex_, EmuCore::do_cmp_near_equal, Joiner_>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices within lhs_vector_ are near-equal to rhs_, intended for safer floating-point equality checks. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons are true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_near(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, IncludeNonContained_, EmuCore::do_cmp_near_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices in the provided range within lhs_vector_ are near-equal to rhs_, intended for safer floating-point equality checks. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_near(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, BeginIndex_, EndIndex_, EmuCore::do_cmp_near_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices within lhs_vector_ are near-equal to rhs_, intended for safer floating-point equality checks. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_near(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, IncludeNonContained_, EmuCore::do_cmp_near_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices in the provided range within lhs_vector_ are near-equal to rhs_, intended for safer floating-point equality checks. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_near(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, EmuCore::do_cmp_near_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion

#pragma region CMP_NOT_NEAR_FUNCS
	/// <summary>
	/// <para> Adaptive near-inequality comparison which changes behaviour based on the provided Rhs_ type, intended for safer floating-point inequality checks. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Equivalent to vector_cmp_any_not_near. </para>
	/// <para> If Rhs_ is none of the above: Compares the magnitude of lhs_vector_ to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
	/// <para> IncludeNonContained_: Unused if Rhs_ is not an EmuMath Vector, otherwise used as in vector_cmp_all_equal. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector appearing on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
	/// <returns>If Rhs_: is an EmuMath Vector: true if all comparisons are true, otherwise false. Otherwise, true if rhs_ is near-equal to lhs_vector_'s magnitude.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_not_near(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp_mag_if_rhs_scalar<false, IncludeNonContained_, EmuCore::do_cmp_not_near_equal, Joiner_>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Adaptive near-inequality comparison which changes behaviour based on the provided Rhs_ type, intended for safer floating-point inequality checks. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Equivalent to vector_cmp_any_not_near. </para>
	/// <para> If Rhs_ is none of the above: Compares the magnitude of lhs_vector_ to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector appearing on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
	/// <returns>
	///		If Rhs_: is an EmuMath Vector: true if all comparisons in the provided range are true, otherwise false. 
	///		Otherwise, true if rhs_ is near-equal to lhs_vector_'s magnitude when calculated using only indices within the provided range.
	/// </returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_not_near(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp_mag_if_rhs_scalar<false, BeginIndex_, EndIndex_, EmuCore::do_cmp_not_near_equal, Joiner_>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices within lhs_vector_ are not near-equal to rhs_, intended for safer floating-point inequality checks. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons are true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_not_near(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, IncludeNonContained_, EmuCore::do_cmp_not_near_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices in the provided range within lhs_vector_ are not near-equal to rhs_, intended for safer floating-point inequality checks. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_not_near(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, BeginIndex_, EndIndex_, EmuCore::do_cmp_not_near_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices within lhs_vector_ are not near-equal to rhs_, intended for safer floating-point inequality checks. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_not_near(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, IncludeNonContained_, EmuCore::do_cmp_not_near_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices in the provided range within lhs_vector_ are not near-equal to rhs_, intended for safer floating-point inequality checks. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_not_near(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, EmuCore::do_cmp_not_near_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion

#pragma region CMP_EQUAL_FUNCS
	/// <summary>
	/// <para> Adaptive equality comparison which changes behaviour based on the provided Rhs_ type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Equivalent to vector_cmp_all_equal. </para>
	/// <para> If Rhs_ is none of the above: Compares the magnitude of lhs_vector_ to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
	/// <para> IncludeNonContained_: Unused if Rhs_ is not an EmuMath Vector, otherwise used as in vector_cmp_all_equal. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector appearing on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
	/// <returns>If Rhs_: is an EmuMath Vector: true if all comparisons are true, otherwise false. Otherwise, true if rhs_ is equal to lhs_vector_'s magnitude.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp_mag_if_rhs_scalar<true, IncludeNonContained_, EmuCore::do_cmp_equal_to, Joiner_>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Adaptive equality comparison which changes behaviour based on the provided Rhs_ type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Equivalent to vector_cmp_all_equal. </para>
	/// <para> If Rhs_ is none of the above: Compares the magnitude of lhs_vector_ to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector appearing on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
	/// <returns>
	///		If Rhs_: is an EmuMath Vector: true if all comparisons in the provided range are true, otherwise false. 
	///		Otherwise, true if rhs_ is equal to lhs_vector_'s magnitude when calculated using only indices within the provided range.
	/// </returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp_mag_if_rhs_scalar<true, BeginIndex_, EndIndex_, EmuCore::do_cmp_equal_to, Joiner_>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices within lhs_vector_ are equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons are true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, IncludeNonContained_, EmuCore::do_cmp_equal_to, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices in the provided range within lhs_vector_ are equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, BeginIndex_, EndIndex_, EmuCore::do_cmp_equal_to, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices within lhs_vector_ are equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, IncludeNonContained_, EmuCore::do_cmp_equal_to, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices in the provided range within lhs_vector_ are equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, EmuCore::do_cmp_equal_to, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion

#pragma region CMP_NOT_EQUAL_FUNCS
	/// <summary>
	/// <para> Adaptive equality comparison which changes behaviour based on the provided Rhs_ type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Equivalent to vector_cmp_any_not_equal. </para>
	/// <para> If Rhs_ is none of the above: Compares the magnitude of lhs_vector_ to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
	/// <para> IncludeNonContained_: Unused if Rhs_ is not an EmuMath Vector, otherwise used as in vector_cmp_all_equal. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector appearing on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
	/// <returns>If Rhs_: is an EmuMath Vector: true if all comparisons are true, otherwise false. Otherwise, true if rhs_ is not equal to lhs_vector_'s magnitude.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_not_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp_mag_if_rhs_scalar<false, IncludeNonContained_, EmuCore::do_cmp_not_equal_to, Joiner_>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Adaptive equality comparison which changes behaviour based on the provided Rhs_ type. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Equivalent to vector_cmp_any_not_equal. </para>
	/// <para> If Rhs_ is none of the above: Compares the magnitude of lhs_vector_ to rhs_, or the square magnitude in allowing situations (where rhs_ may be squared). </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector appearing on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector appearing on the right of per-element comparison, or scalar appearing on the right of magnitude comparison.</param>
	/// <returns>
	///		If Rhs_: is an EmuMath Vector: true if all comparisons in the provided range are true, otherwise false. 
	///		Otherwise, true if rhs_ is not equal to lhs_vector_'s magnitude when calculated using only indices within the provided range.
	/// </returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_not_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp_mag_if_rhs_scalar<false, BeginIndex_, EndIndex_, EmuCore::do_cmp_not_equal_to, Joiner_>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices within lhs_vector_ are not equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons are true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_not_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, IncludeNonContained_, EmuCore::do_cmp_not_equal_to, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices in the provided range within lhs_vector_ are not equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_not_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, BeginIndex_, EndIndex_, EmuCore::do_cmp_not_equal_to, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices within lhs_vector_ are not equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_not_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, IncludeNonContained_, EmuCore::do_cmp_not_equal_to, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices in the provided range within lhs_vector_ are not equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_not_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, EmuCore::do_cmp_not_equal_to, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion

#pragma region CMP_GREATER_FUNCS
	/// <summary>
	/// <para> Returns true if the magnitude of lhs_vector_ is greater than that of rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, lhs_vector_'s magnitude will be compared with rhs_ directly. </para>
	/// <para> 
	///		IncludeNonContained_: If true, all elements of each Vector will be used to determine their magnitude. 
	///		If false, only elements up to the end of the smallest Vector will be used to determine magnitude. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector whose magnitude appears on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
	/// <returns>True if lhs_vector_'s magnitude is greater than that of rhs_, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_greater(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		return _vector_underlying::_vector_cmp_mag<IncludeNonContained_, EmuCore::do_cmp_greater>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if the magnitude of lhs_vector_ is greater than that of rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, lhs_vector_'s magnitude will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors to calculate their magnitude. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors to calculate their magnitude. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector whose magnitude appears on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
	/// <returns>True if lhs_vector_'s magnitude is greater than that of rhs_, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_greater(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		return _vector_underlying::_vector_cmp_mag<BeginIndex_, EndIndex_, EmuCore::do_cmp_greater>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices within lhs_vector_ are greater than rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons are true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_greater(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, IncludeNonContained_, EmuCore::do_cmp_greater, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices in the provided range within lhs_vector_ are greater than rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_greater(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, BeginIndex_, EndIndex_, EmuCore::do_cmp_greater, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices within lhs_vector_ are greater than rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_greater(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, IncludeNonContained_, EmuCore::do_cmp_greater, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices in the provided range within lhs_vector_ are greater than rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_greater(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, EmuCore::do_cmp_greater, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion

#pragma region CMP_LESS_FUNCS
	/// <summary>
	/// <para> Returns true if the magnitude of lhs_vector_ is less than that of rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, lhs_vector_'s magnitude will be compared with rhs_ directly. </para>
	/// <para> 
	///		IncludeNonContained_: If true, all elements of each Vector will be used to determine their magnitude. 
	///		If false, only elements up to the end of the smallest Vector will be used to determine magnitude. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector whose magnitude appears on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
	/// <returns>True if lhs_vector_'s magnitude is less than that of rhs_, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_less(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		return _vector_underlying::_vector_cmp_mag<IncludeNonContained_, EmuCore::do_cmp_less>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if the magnitude of lhs_vector_ is less than that of rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, lhs_vector_'s magnitude will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors to calculate their magnitude. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors to calculate their magnitude. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector whose magnitude appears on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
	/// <returns>True if lhs_vector_'s magnitude is less than that of rhs_, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_less(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		return _vector_underlying::_vector_cmp_mag<BeginIndex_, EndIndex_, EmuCore::do_cmp_less>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices within lhs_vector_ are less than rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons are true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_less(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, IncludeNonContained_, EmuCore::do_cmp_less, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices in the provided range within lhs_vector_ are less than rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_less(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, BeginIndex_, EndIndex_, EmuCore::do_cmp_less, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices within lhs_vector_ are greater than rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_less(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, IncludeNonContained_, EmuCore::do_cmp_less, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices in the provided range within lhs_vector_ are greater than rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_less(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, EmuCore::do_cmp_less, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion

#pragma region CMP_GREATER_EQUAL_FUNCS
	/// <summary>
	/// <para> Returns true if the magnitude of lhs_vector_ is greater than or equal to that of rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, lhs_vector_'s magnitude will be compared with rhs_ directly. </para>
	/// <para> 
	///		IncludeNonContained_: If true, all elements of each Vector will be used to determine their magnitude. 
	///		If false, only elements up to the end of the smallest Vector will be used to determine magnitude. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector whose magnitude appears on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
	/// <returns>True if lhs_vector_'s magnitude is greater than or equal to that of rhs_, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_greater_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		return _vector_underlying::_vector_cmp_mag<IncludeNonContained_, EmuCore::do_cmp_greater_equal>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if the magnitude of lhs_vector_ is greater than or equal to that of rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, lhs_vector_'s magnitude will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors to calculate their magnitude. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors to calculate their magnitude. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector whose magnitude appears on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
	/// <returns>True if lhs_vector_'s magnitude is greater than or equal to that of rhs_, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_greater_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		return _vector_underlying::_vector_cmp_mag<BeginIndex_, EndIndex_, EmuCore::do_cmp_greater_equal>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices within lhs_vector_ are greater than or equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons are true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_greater_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, IncludeNonContained_, EmuCore::do_cmp_greater_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices in the provided range within lhs_vector_ are greater than or equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_greater_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, BeginIndex_, EndIndex_, EmuCore::do_cmp_greater_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices within lhs_vector_ are greater than or equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_greater_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, IncludeNonContained_, EmuCore::do_cmp_greater_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices in the provided range within lhs_vector_ are greater than or equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_greater_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, EmuCore::do_cmp_greater_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion

#pragma region CMP_LESS_EQUAL_FUNCS
	/// <summary>
	/// <para> Returns true if the magnitude of lhs_vector_ is less than or equal to that of rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, lhs_vector_'s magnitude will be compared with rhs_ directly. </para>
	/// <para> 
	///		IncludeNonContained_: If true, all elements of each Vector will be used to determine their magnitude. 
	///		If false, only elements up to the end of the smallest Vector will be used to determine magnitude. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector whose magnitude appears on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
	/// <returns>True if lhs_vector_'s magnitude is less than or equal to that of rhs_, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_less_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		return _vector_underlying::_vector_cmp_mag<IncludeNonContained_, EmuCore::do_cmp_less_equal>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if the magnitude of lhs_vector_ is less than or equal to that of rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Both Vector's magnitudes will be compared. Otherwise, lhs_vector_'s magnitude will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors to calculate their magnitude. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors to calculate their magnitude. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector whose magnitude appears on the left of comparison.</param>
	/// <param name="rhs_">EmuMath Vector whose magnitude appears on the right of comparison, or scalar appearing on the right of comparison.</param>
	/// <returns>True if lhs_vector_'s magnitude is less than or equal to that of rhs_, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_less_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		return _vector_underlying::_vector_cmp_mag<BeginIndex_, EndIndex_, EmuCore::do_cmp_less_equal>(lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices within lhs_vector_ are less than or equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons are true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_less_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, IncludeNonContained_, EmuCore::do_cmp_less_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if all indices in the provided range within lhs_vector_ are less than or equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if all comparisons within the provided range are true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_all_less_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, BeginIndex_, EndIndex_, EmuCore::do_cmp_less_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices within lhs_vector_ are less than or equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para>
	///		IncludeNonContained_: If true, non-contained indices will be compared until the largest Vector is fully compared. 
	///		If false, comparisons will only be performed until the end of the smallest Vector. 
	///		Has no effect if Rhs_ is not an EmuMath Vector. 
	///		Defaults to true.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison is true, otherwise false.</returns>
	template<bool IncludeNonContained_ = true, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_less_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, IncludeNonContained_, EmuCore::do_cmp_less_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Returns true if any indices in the provided range within lhs_vector_ are less than or equal to rhs_. </para>
	/// <para> If Rhs_ is an EmuMath Vector: Respective index elements will be compared. Otherwise, indices in lhs_vector_ will be compared with rhs_ directly. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading elements from Vectors for comparisons. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading elements from Vectors for comparisons. </para>
	/// </summary>
	/// <param name="lhs_vector_">: EmuMath Vector whose individual elements will appear on the left-hand side of comparisons.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of comparisons.</param>
	/// <returns>True if at least 1 comparison within the provided range is true, otherwise false.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool vector_cmp_any_less_equal(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, EmuCore::do_cmp_less_equal, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion
}

#endif
