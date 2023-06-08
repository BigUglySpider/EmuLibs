#ifndef EMU_MATH_FAST_MATRIX_MISC_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_MATRIX_MISC_ARITHMETIC_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region ROUNDS
	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_abs(FastMatrix_&& fast_matrix_)
		-> typename std::remove_cvref<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_fast_matrix_abs<false>(std::forward<FastMatrix_>(fast_matrix_));
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
	constexpr inline void fast_matrix_abs_assign(EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& in_out_fast_matrix_)
	{
		_fast_matrix_underlying::_fast_matrix_abs<true>(in_out_fast_matrix_);
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
	[[nodiscard]] constexpr inline auto fast_matrix_min
	(
		const EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& a_,
		const EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& b_
	) -> EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>
	{
		return _fast_matrix_underlying::_fast_matrix_min_or_max<false, false>(a_, b_);
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
	constexpr inline void fast_matrix_min_assign
	(
		EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& in_out_a_,
		const EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& b_
	)
	{
		_fast_matrix_underlying::_fast_matrix_min_or_max<false, true>(in_out_a_, b_);
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_min(FastMatrix_&& fast_matrix_)
		-> typename std::remove_cvref<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_fast_matrix_min_or_max<false, false, void>(std::forward<FastMatrix_>(fast_matrix_));
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
	constexpr inline void fast_matrix_min_assign(EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& in_out_fast_matrix_)
	{
		return _fast_matrix_underlying::_fast_matrix_min_or_max<false, true, void>(in_out_fast_matrix_);
	}

	template<class OutScalar_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_min_scalar(FastMatrix_&& fast_matrix_)
		-> typename std::remove_cvref<OutScalar_>::type
	{
		return _fast_matrix_underlying::_fast_matrix_min_or_max<false, false, OutScalar_>(std::forward<FastMatrix_>(fast_matrix_));
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_min_scalar(FastMatrix_&& fast_matrix_)
		-> typename std::remove_cvref_t<FastMatrix_>::value_type
	{
		return _fast_matrix_underlying::_fast_matrix_min_or_max<false, false, typename std::remove_cvref_t<FastMatrix_>::value_type>(std::forward<FastMatrix_>(fast_matrix_));
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
	[[nodiscard]] constexpr inline auto fast_matrix_max
	(
		const EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& a_,
		const EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& b_
	) -> EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>
	{
		return _fast_matrix_underlying::_fast_matrix_min_or_max<true, false>(a_, b_);
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
	constexpr inline void fast_matrix_max_assign
	(
		EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& in_out_a_,
		const EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& b_
	)
	{
		_fast_matrix_underlying::_fast_matrix_min_or_max<true, true>(in_out_a_, b_);
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_max(FastMatrix_&& fast_matrix_)
		-> typename std::remove_cvref<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_fast_matrix_min_or_max<true, false, void>(std::forward<FastMatrix_>(fast_matrix_));
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
	constexpr inline void fast_matrix_max_assign(EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>& in_out_fast_matrix_)
	{
		return _fast_matrix_underlying::_fast_matrix_min_or_max<true, true, void>(in_out_fast_matrix_);
	}

	template<class OutScalar_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_max_scalar(FastMatrix_&& fast_matrix_)
		-> typename std::remove_cvref<OutScalar_>::type
	{
		return _fast_matrix_underlying::_fast_matrix_min_or_max<true, false, OutScalar_>(std::forward<FastMatrix_>(fast_matrix_));
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_max_scalar(FastMatrix_&& fast_matrix_)
		-> typename std::remove_cvref_t<FastMatrix_>::value_type
	{
		return _fast_matrix_underlying::_fast_matrix_min_or_max<true, false, typename std::remove_cvref_t<FastMatrix_>::value_type>(std::forward<FastMatrix_>(fast_matrix_));
	}
#pragma endregion
}

#endif
