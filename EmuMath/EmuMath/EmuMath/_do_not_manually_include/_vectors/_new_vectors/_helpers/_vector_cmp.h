#ifndef EMU_MATH_NEW_VECTOR_CMP_H_INC_
#define EMU_MATH_NEW_VECTOR_CMP_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../../EmuCore/Functors/Comparators.h"

// CONTAINS:
// --- cmp_all
// --- cmp_any

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
	[[nodiscard]] constexpr inline bool new_vector_cmp_all(const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_, Cmp_ cmp_)
	{
		using cmp_ref_ = std::add_lvalue_reference_t<Cmp_>;
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, IncludeNonContained_, cmp_ref_, Joiner_>(cmp_, Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	template<class Cmp_, bool IncludeNonContained_ = true, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool new_vector_cmp_all(const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
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
	[[nodiscard]] constexpr inline bool new_vector_cmp_all(const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
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
	[[nodiscard]] constexpr inline bool new_vector_cmp_all(const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_, Cmp_ cmp_)
	{
		using cmp_ref_ = std::add_lvalue_reference_t<Cmp_>;
		using Joiner_ = std::logical_and<void>;
		return _vector_underlying::_vector_cmp<true, BeginIndex_, EndIndex_, cmp_ref_, Joiner_>(cmp_, Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	template<class Cmp_, std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool new_vector_cmp_all(const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
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
	[[nodiscard]] constexpr inline bool new_vector_cmp_all(const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
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
	[[nodiscard]] constexpr inline bool new_vector_cmp_any(const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_, Cmp_ cmp_)
	{
		using cmp_ref_ = std::add_lvalue_reference_t<Cmp_>;
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, IncludeNonContained_, cmp_ref_, Joiner_>(cmp_, Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	template<class Cmp_, bool IncludeNonContained_ = true, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool new_vector_cmp_any(const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
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
	[[nodiscard]] constexpr inline bool new_vector_cmp_any(const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
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
	[[nodiscard]] constexpr inline bool new_vector_cmp_any(const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_, Cmp_ cmp_)
	{
		using cmp_ref_ = std::add_lvalue_reference_t<Cmp_>;
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, cmp_ref_, Joiner_>(cmp_, Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}

	template<class Cmp_, std::size_t BeginIndex_, std::size_t EndIndex_, typename Rhs_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline bool new_vector_cmp_any(const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
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
	[[nodiscard]] constexpr inline bool new_vector_cmp_any(const EmuMath::NewVector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	{
		using Joiner_ = std::logical_or<void>;
		return _vector_underlying::_vector_cmp<false, BeginIndex_, EndIndex_, CmpTemplate_, Joiner_>(Joiner_(), lhs_vector_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion
}

#endif
