#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_MAT_MULT_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_MAT_MULT_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template
	<
		EmuConcepts::EmuFastMatrix Lhs_, EmuConcepts::EmuFastMatrix Rhs_,
		std::size_t RegisterIndex_, std::size_t LhsRowIndex_, std::size_t...RhsRowIndicesExcept0_
	>
	[[nodiscard]] static constexpr inline auto _multiply_chunk_segment_rm_rm(Lhs_&& lhs_, Rhs_&& rhs_)
		-> typename EmuMath::TMP::fast_matrix_register_type<Lhs_>::type
	{
		using _lhs_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
		constexpr std::size_t calc_per_element_per_width = _lhs_uq::per_element_width;
		if constexpr (sizeof...(RhsRowIndicesExcept0_) == 0)
		{
			return EmuSIMD::mul_all<calc_per_element_per_width>
			(
				std::forward<Lhs_>(lhs_).template GetRegisterOfIndex<0, LhsRowIndex_>(),
				std::forward<Rhs_>(rhs_).template GetRegister<0, RegisterIndex_>()
			);
		}
		else
		{
			typename EmuMath::TMP::fast_matrix_register_type<Lhs_>::type result = EmuSIMD::mul_all<calc_per_element_per_width>
			(
				std::forward<Lhs_>(lhs_).template GetRegisterOfIndex<0, LhsRowIndex_>(),
				std::forward<Rhs_>(rhs_).template GetRegister<0, RegisterIndex_>()
			);

			(
				(
					result = EmuSIMD::fmadd<calc_per_element_per_width>
					(
						std::forward<Lhs_>(lhs_).template GetRegisterOfIndex<RhsRowIndicesExcept0_, LhsRowIndex_>(),
						std::forward<Rhs_>(rhs_).template GetRegister<RhsRowIndicesExcept0_, RegisterIndex_>(),
						result
					)
				), ...
			);
			return result;
		}
	}

	template
	<
		std::size_t LhsRowIndex_, EmuConcepts::EmuFastMatrix Lhs_, EmuConcepts::EmuFastMatrix Rhs_,
		std::size_t...LhsRowIndices_, std::size_t...RhsRowIndicesExcept0_, std::size_t...RegisterIndices_
	>
	[[nodiscard]] static constexpr inline auto _do_multiply_multi_registers_for_chunk_rm_rm
	(
		Lhs_&& lhs_,
		Rhs_&& rhs_,
		std::index_sequence<RhsRowIndicesExcept0_...> rhs_row_indices_except_0_,
		std::index_sequence<RegisterIndices_...> register_indices_
	) -> typename EmuMath::TMP::fast_matrix_multiply_result_t<Lhs_, Rhs_>::major_chunk_type
	{
		using _lhs_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
		using _rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
		using _out_mat = typename EmuMath::TMP::fast_matrix_multiply_result<Lhs_, Rhs_>::type;
		return typename _out_mat::major_chunk_type
		({
			_multiply_chunk_segment_rm_rm<Lhs_, Rhs_, RegisterIndices_, LhsRowIndex_, RhsRowIndicesExcept0_...>
			(
				std::forward<Lhs_>(lhs_),
				std::forward<Rhs_>(rhs_)
			)...
		});
	}

	template
	<
		EmuConcepts::EmuFastMatrix Lhs_, EmuConcepts::EmuFastMatrix Rhs_,
		std::size_t...LhsRowIndices_, std::size_t...RhsRowIndicesExcept0_, std::size_t...RegisterIndices_
	>
	[[nodiscard]] static constexpr inline auto _do_multiply_multi_registers_rm_rm
	(
		Lhs_&& lhs_,
		Rhs_&& rhs_,
		std::index_sequence<LhsRowIndices_...> lhs_row_indices_,
		std::index_sequence<RhsRowIndicesExcept0_...> rhs_row_indices_except_0_,
		std::index_sequence<RegisterIndices_...> register_indices_
	) -> typename EmuMath::TMP::fast_matrix_multiply_result<Lhs_, Rhs_>::type
	{
		using _lhs_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
		using _rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
		using _out_mat = typename EmuMath::TMP::fast_matrix_multiply_result<Lhs_, Rhs_>::type;
		return _out_mat
		(
			_do_multiply_multi_registers_for_chunk_rm_rm<LhsRowIndices_>
			(
				std::forward<Lhs_>(lhs_),
				std::forward<Rhs_>(rhs_),
				std::index_sequence<RhsRowIndicesExcept0_...>(),
				std::index_sequence<RegisterIndices_...>()
			)...
		);
	}

	template<EmuConcepts::EmuFastMatrix Lhs_, EmuConcepts::EmuFastMatrix Rhs_, std::size_t...LhsRowIndices_, std::size_t...RhsRowIndicesExcept0_>
	[[nodiscard]] static constexpr inline auto _do_multiply_rm_rm
	(
		Lhs_&& lhs_,
		Rhs_&& rhs_,
		std::index_sequence<LhsRowIndices_...> lhs_row_indices_,
		std::index_sequence<RhsRowIndicesExcept0_...> rhs_row_indices_except_0_
	) -> typename EmuMath::TMP::fast_matrix_multiply_result<Lhs_, Rhs_>::type
	{
		using _lhs_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
		using _rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
		using _out_mat = typename EmuMath::TMP::fast_matrix_multiply_result<Lhs_, Rhs_>::type;

		if constexpr (_out_mat::num_registers_per_major > 1)
		{
			using register_indices = std::make_index_sequence<_out_mat::num_registers_per_major>;
			return _do_multiply_multi_registers_rm_rm
			(
				std::forward<Lhs_>(lhs_),
				std::forward<Rhs_>(rhs_),
				std::index_sequence<LhsRowIndices_...>(),
				std::index_sequence<RhsRowIndicesExcept0_...>(),
				register_indices()
			);
		}
		else
		{
			return _out_mat
			(
				_multiply_chunk_segment_rm_rm<Lhs_, Rhs_, 0, LhsRowIndices_, RhsRowIndicesExcept0_...>
				(
					std::forward<Lhs_>(lhs_),
					std::forward<Rhs_>(rhs_)
				)...
			);
		}
	}
}

#endif
