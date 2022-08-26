#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_ARITHMETIC_H_INC_ 1

#include "_fast_matrix_tmp.h"
#include "../../../Matrix.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<std::size_t RhsColumnIndex_, class LhsMatrix_, class RhsMatrix_, std::size_t...LhsColumnIndicesExcept0_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsMatrix_, RhsMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _std_multiply_impl_lhs_cm
	(
		const LhsMatrix_& lhs_,
		const RhsMatrix_& rhs_,
		std::index_sequence<LhsColumnIndicesExcept0_...> lhs_major_indices_except_0_
	)
	{
		using _rhs_matrix_uq = typename EmuCore::TMP::remove_ref_cv<RhsMatrix_>::type;
		constexpr bool out_column_major = true;

		const auto& major_rhs = rhs_.template GetMajor<RhsColumnIndex_>();
		if constexpr (sizeof...(LhsColumnIndicesExcept0_) != 0)
		{
			auto out_chunk = lhs_.template GetMajor<0>().Multiply(rhs_.template AllAsIndexRegister<RhsColumnIndex_, 0>());

			(
				(
					out_chunk = lhs_.template GetMajor<LhsColumnIndicesExcept0_>().Fmadd
					(
						rhs_.template AllAsIndexRegister<RhsColumnIndex_, LhsColumnIndicesExcept0_>(),
						out_chunk
					)
				), ...
			);

			return out_chunk;
		}
		else
		{
			return lhs_.template GetMajor<0>().Multiply(major_rhs.template AllAsIndexRegister<0>());
		}
	}

	template<std::size_t RhsRowIndex_, class LhsMatrix_, class RhsMatrix_, std::size_t...LhsRowIndicesExcept0_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsMatrix_, RhsMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _std_multiply_impl_lhs_rm_rhs_rm
	(
		const LhsMatrix_& lhs_,
		const RhsMatrix_& rhs_,
		std::index_sequence<LhsRowIndicesExcept0_...> lhs_major_indices_except_0_
	)
	{
		using _rhs_mat_uq = typename EmuCore::TMP::remove_ref_cv<RhsMatrix_>::type;
		if constexpr (sizeof...(LhsRowIndicesExcept0_))
		{
			auto out_chunk = rhs_.template GetMajor<0>().Multiply(lhs_.template AllAsIndexRegister<0, RhsRowIndex_>());

			(
				(
					out_chunk = rhs_.template GetMajor<LhsRowIndicesExcept0_>().Fmadd
					(
						lhs_.template AllAsIndexRegister<LhsRowIndicesExcept0_, RhsRowIndex_>(),
						out_chunk
					)
				), ...
			);

			return out_chunk;
		}
		else
		{
			return rhs_.template GetMajor<0>().Multiply(lhs_.template AllAsIndexRegister<0, RhsRowIndex_>());
		}
	}

	template<class LhsMatrix_, class RhsMatrix_, std::size_t...RhsMajorIndices_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsMatrix_, RhsMatrix_>
	[[nodiscard]] constexpr inline auto _std_multiply
	(
		const LhsMatrix_& lhs_,
		const RhsMatrix_& rhs_,
		std::index_sequence<RhsMajorIndices_...> rhs_major_indices_
	) -> EmuMath::FastMatrix
		<
			EmuCore::TMP::remove_ref_cv_t<RhsMatrix_>::num_columns,
			EmuCore::TMP::remove_ref_cv_t<LhsMatrix_>::num_rows,
			typename EmuCore::TMP::remove_ref_cv_t<LhsMatrix_>::value_type,
			EmuCore::TMP::remove_ref_cv_t<LhsMatrix_>::is_column_major,
			EmuCore::TMP::remove_ref_cv_t<LhsMatrix_>::register_width
		>
	{
		using lhs_uq = typename EmuCore::TMP::remove_ref_cv<LhsMatrix_>::type;
		using rhs_uq = typename EmuCore::TMP::remove_ref_cv<RhsMatrix_>::type;
		using lhs_indices = EmuCore::TMP::make_offset_index_sequence<1, lhs_uq::num_major_elements - 1>;
		using _out_mat_type = EmuMath::FastMatrix
		<
			rhs_uq::num_columns,
			lhs_uq::num_rows,
			typename lhs_uq::value_type,
			lhs_uq::is_column_major,
			lhs_uq::register_width
		>;

		if constexpr(lhs_uq::is_column_major)
		{
			return _out_mat_type
			(
				_std_multiply_impl_lhs_cm<RhsMajorIndices_>
				(
					lhs_,
					rhs_,
					lhs_indices()
				)...
			);
		}
		else
		{
			if constexpr (rhs_uq::is_column_major)
			{
				// Worst case scenario; we don't have a fallback for row-major rhs as we do in column-major, so we have to convert rhs to row-major
				// --- This means we're performing a transpose before multiplication
				auto rhs_rm = rhs_.ToOtherMajor();
				return _out_mat_type
				(
					_std_multiply_impl_lhs_rm_rhs_rm<RhsMajorIndices_>
					(
						lhs_,
						rhs_rm,
						lhs_indices()
					)...
				);
			}
			else
			{
				return _out_mat_type
				(
					_std_multiply_impl_lhs_rm_rhs_rm<RhsMajorIndices_>
					(
						lhs_,
						rhs_,
						lhs_indices()
					)...
				);
			}
		}
	}
}

#endif
