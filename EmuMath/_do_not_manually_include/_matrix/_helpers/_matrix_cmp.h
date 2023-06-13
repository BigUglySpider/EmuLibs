#ifndef EMU_MATH_MATRIX_CMP_H_INC_
#define EMU_MATH_MATRIX_CMP_H_INC_ 1

#include "_common_matrix_helper_includes.h"

// CONTAINS:
// --- cmp
// --- cmp_equal
// --- cmp_not_equal
// --- cmp_any_equal
// --- cmp_any_not_equal
// --- cmp_any_less
// --- cmp_any_greater
// --- cmp_any_less_equal
// --- cmp_any_greater_equal
// --- cmp_all_equal
// --- cmp_all_not_equal
// --- cmp_all_less
// --- cmp_all_greater
// --- cmp_all_less_equal
// --- cmp_all_greater_equal
// --- ...Including their ranged variants

namespace EmuMath::Helpers
{
#pragma region CUSTOM_CMPS
	template<bool RequiresAllTrue_, bool IncludeNonContained_ = false, class Cmp_, EmuConcepts::EmuMatrix LhsMatrix_, class...Args_>
	[[nodiscard]] constexpr inline bool matrix_cmp(Cmp_&& cmp_, LhsMatrix_&& lhs_matrix_, Args_&&...args_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, RequiresAllTrue_>
		(
			std::forward<Cmp_>(cmp_),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Args_>(args_)...
		);
	}

	template<bool RequiresAllTrue_, std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Cmp_, EmuConcepts::EmuMatrix LhsMatrix_, class...Args_>
	[[nodiscard]] constexpr inline bool matrix_cmp(Cmp_&& cmp_, LhsMatrix_&& lhs_matrix_, Args_&&...args_)
	{
		return _matrix_underlying::_matrix_cmp_range<RequiresAllTrue_, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			std::forward<Cmp_>(cmp_),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Args_>(args_)...
		);
	}
#pragma endregion

#pragma region DEFAULT_CMPS
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, EmuConcepts::EmuMatrix RhsMatrix_>
	[[nodiscard]] constexpr inline bool matrix_cmp_equal(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_equal_to<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<RhsMatrix_>(rhs_matrix_)
		);
	}

	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, EmuConcepts::EmuMatrix RhsMatrix_>
	[[nodiscard]] constexpr inline bool matrix_cmp_not_equal(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_not_equal_to<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<RhsMatrix_>(rhs_matrix_)
		);
	}

	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, EmuConcepts::EmuMatrix RhsMatrix_>
	[[nodiscard]] constexpr inline bool matrix_cmp_near(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<RhsMatrix_>(rhs_matrix_)
		);
	}

	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, EmuConcepts::EmuMatrix RhsMatrix_, class Epsilon_>
	[[nodiscard]] constexpr inline bool matrix_cmp_near(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_, Epsilon_&& epsilon_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<RhsMatrix_>(rhs_matrix_),
			std::forward<Epsilon_>(epsilon_)
		);
	}

	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, EmuConcepts::EmuMatrix RhsMatrix_>
	[[nodiscard]] constexpr inline bool matrix_cmp_not_near(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_not_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<RhsMatrix_>(rhs_matrix_)
		);
	}

	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, EmuConcepts::EmuMatrix RhsMatrix_, class Epsilon_>
	[[nodiscard]] constexpr inline bool matrix_cmp_not_near(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_, Epsilon_&& epsilon_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_not_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<RhsMatrix_>(rhs_matrix_),
			std::forward<Epsilon_>(epsilon_)
		);
	}
#pragma endregion

#pragma region CMP_ANY
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_equal_to<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_not_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_not_equal_to<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_near_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_, class Epsilon_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_, Epsilon_&& epsilon_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_near_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_),
			std::forward<Epsilon_>(epsilon_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_not_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_not_near_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_, class Epsilon_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_not_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_, Epsilon_&& epsilon_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_not_near_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_),
			std::forward<Epsilon_>(epsilon_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_greater(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_greater<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_less(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_less<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_greater_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_greater_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_less_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, false>
		(
			EmuCore::do_cmp_less_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region CMP_ALL
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_equal_to<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_not_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_not_equal_to<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_near_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_, class Epsilon_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_, Epsilon_&& epsilon_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_near_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_),
			std::forward<Epsilon_>(epsilon_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_not_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_not_near_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_, class Epsilon_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_not_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_, Epsilon_&& epsilon_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_not_near_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_),
			std::forward<Epsilon_>(epsilon_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_greater(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_greater<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_less(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_less<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_greater_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_greater_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<bool IncludeNonContained_ = false, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_less_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp<IncludeNonContained_, true>
		(
			EmuCore::do_cmp_less_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region DEFAULT_CMP_RANGE
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, EmuConcepts::EmuMatrix RhsMatrix_>
	[[nodiscard]] constexpr inline bool matrix_cmp_equal(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_equal_to<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<RhsMatrix_>(rhs_matrix_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, EmuConcepts::EmuMatrix RhsMatrix_>
	[[nodiscard]] constexpr inline bool matrix_cmp_not_equal(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_not_equal_to<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<RhsMatrix_>(rhs_matrix_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, EmuConcepts::EmuMatrix RhsMatrix_>
	[[nodiscard]] constexpr inline bool matrix_cmp_near(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<RhsMatrix_>(rhs_matrix_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, EmuConcepts::EmuMatrix RhsMatrix_, class Epsilon_>
	[[nodiscard]] constexpr inline bool matrix_cmp_near(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_, Epsilon_&& epsilon_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<RhsMatrix_>(rhs_matrix_),
			std::forward<Epsilon_>(epsilon_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, EmuConcepts::EmuMatrix RhsMatrix_>
	[[nodiscard]] constexpr inline bool matrix_cmp_not_near(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_not_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<RhsMatrix_>(rhs_matrix_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, EmuConcepts::EmuMatrix RhsMatrix_, class Epsilon_>
	[[nodiscard]] constexpr inline bool matrix_cmp_not_near(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_, Epsilon_&& epsilon_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_not_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<RhsMatrix_>(rhs_matrix_),
			std::forward<Epsilon_>(epsilon_)
		);
	}
#pragma endregion

#pragma region CMP_ANY_RANGE
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_equal_to<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_not_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_not_equal_to<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}

	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}

	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_, class Epsilon_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_, Epsilon_&& epsilon_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_),
			std::forward<Epsilon_>(epsilon_)
		);
	}

	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_not_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_not_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}

	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_, class Epsilon_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_not_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_, Epsilon_&& epsilon_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_not_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_),
			std::forward<Epsilon_>(epsilon_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_greater(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_greater<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_less(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_less<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_greater_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_greater_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_any_less_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<false, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_less_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region CMP_ALL_RANGE
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_equal_to<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_not_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_not_equal_to<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}

	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}

	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_, class Epsilon_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_, Epsilon_&& epsilon_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_),
			std::forward<Epsilon_>(epsilon_)
		);
	}

	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_not_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_not_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}

	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_, class Epsilon_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_not_near(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_, Epsilon_&& epsilon_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_not_near_equal<void, void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_),
			std::forward<Epsilon_>(epsilon_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_greater(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_greater<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_less(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_less<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_greater_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_greater_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
	
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline bool matrix_cmp_all_less_equal(LhsMatrix_&& lhs_matrix_, Rhs_&& rhs_)
	{
		return _matrix_underlying::_matrix_cmp_range<true, BeginColumn_, BeginRow_, EndColumn_, EndRow_>
		(
			EmuCore::do_cmp_less_equal<void, void>(),
			std::forward<LhsMatrix_>(lhs_matrix_),
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion
}

#endif
