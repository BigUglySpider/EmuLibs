#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_ARITHMETIC_H_INC_ 1

#include "_fast_matrix_tmp.h"
#include "../../../Matrix.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, EmuConcepts::EmuFastMatrix OutMatrix_, class LhsMatrix_, class RhsMatrix_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsMatrix_, RhsMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _naive_multiply_index_rm_cm(LhsMatrix_&& lhs_, RhsMatrix_&& rhs_)
	{
		return lhs_.major_vectors[ColumnIndex_].DotScalar(rhs_.major_vectors[RowIndex_]);
	}

	template<std::size_t RhsColumnIndex_, class LhsMatrix_, class RhsMatrix_, std::size_t...LhsColumnIndicesExcept0_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsMatrix_, RhsMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _updated_multiply_major_out_impl_lhs_cm
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

	template<std::size_t RhsRowIndex_, class LhsMatrix_, class RhsMatrix_, std::size_t...RhsRowIndicesExcept0_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsMatrix_, RhsMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _updated_multiply_major_out_impl_lhs_rm_rhs_rm
	(
		const LhsMatrix_& lhs_,
		const RhsMatrix_& rhs_,
		std::index_sequence<RhsRowIndicesExcept0_...> lhs_major_indices_except_0_
	)
	{
		using _rhs_mat_uq = typename EmuCore::TMP::remove_ref_cv<RhsMatrix_>::type;		
		if constexpr (sizeof...(RhsRowIndicesExcept0_))
		{
			auto out_chunk = rhs_.template GetMajor<0>().Multiply(lhs_.template AllAsIndexRegister<0, RhsRowIndex_>());
			(
				(
					out_chunk = rhs_.template GetMajor<RhsRowIndicesExcept0_>().Fmadd
					(
						lhs_.template AllAsIndexRegister<RhsRowIndicesExcept0_, RhsRowIndex_>(),
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
	[[nodiscard]] constexpr inline decltype(auto) _updated_multiply_lhs_cm
	(
		const LhsMatrix_& lhs_,
		const RhsMatrix_& rhs_,
		std::index_sequence<RhsMajorIndices_...> rhs_major_indices_
	)
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
				_updated_multiply_major_out_impl_lhs_cm<RhsMajorIndices_>
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
				auto rhs_rm = rhs_.ToOtherMajor();
				return _out_mat_type
				(
					_updated_multiply_major_out_impl_lhs_rm_rhs_rm<RhsMajorIndices_>
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
					_updated_multiply_major_out_impl_lhs_rm_rhs_rm<RhsMajorIndices_>
					(
						lhs_,
						rhs_,
						lhs_indices()
					)...
				);
			}
		}
	}

	template<EmuConcepts::EmuFastMatrix OutMatrix_, class LhsMatrix_, class RhsMatrix_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsMatrix_, RhsMatrix_>
	[[nodiscard]] constexpr inline auto _naive_multiply_impl_rm_cm
	(
		LhsMatrix_&& lhs_,
		RhsMatrix_&& rhs_,
		std::index_sequence<ColumnIndices_...>,
		std::index_sequence<RowIndices_...>
	)
	{
		return OutMatrix_
		(
			typename OutMatrix_::matrix_type
			(
				_naive_multiply_index_rm_cm<ColumnIndices_, RowIndices_, OutMatrix_>
				(
					std::forward<LhsMatrix_>(lhs_),
					std::forward<RhsMatrix_>(rhs_)
				)...
			)
		);
	}
}

#endif
