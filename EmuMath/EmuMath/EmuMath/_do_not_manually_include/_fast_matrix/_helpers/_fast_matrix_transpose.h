#ifndef EMU_MATH_FAST_MATRIX_TRANSPOSE_H_INC_
#define EMU_MATH_FAST_MATRIX_TRANSPOSE_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"
#include "_fast_matrix_store.h"

namespace EmuMath::Helpers
{
	template<bool OutColumnMajor_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_transpose(FastMatrix_&& in_matrix_)
		-> typename EmuMath::TMP::fast_matrix_transpose_result<FastMatrix_, OutColumnMajor_>::type
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		if constexpr (OutColumnMajor_ != _in_fast_mat_uq::is_column_major)
		{
			// Cheap transpose as we're just changing how the majors are interpreted, but the majors themselves are the same
			if constexpr (std::is_lvalue_reference_v<FastMatrix_>)
			{
				return typename EmuMath::TMP::fast_matrix_transpose_result<FastMatrix_, OutColumnMajor_>::type
				(
					in_matrix_.major_chunks
				);
			}
			else
			{
				return typename EmuMath::TMP::fast_matrix_transpose_result<FastMatrix_, OutColumnMajor_>::type
				(
					std::move(std::forward<FastMatrix_>(in_matrix_).major_chunks)
				);
			}			
		}
		else
		{
			// Same major so we need to actually do something
			return _fast_matrix_underlying::_make_transpose_same_major(std::forward<FastMatrix_>(in_matrix_));
		}
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_transpose(FastMatrix_&& in_matrix_)
		-> typename EmuMath::TMP::fast_matrix_transpose_result<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_make_transpose_same_major(std::forward<FastMatrix_>(in_matrix_));
	}
}

#endif
