#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_IDENTITY_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_IDENTITY_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
#pragma region MAKE_FUNCS
	template<EmuConcepts::Arithmetic Value_, EmuConcepts::KnownSIMD OutRegister_, std::size_t Width_, std::size_t OneIndex_, std::size_t...RegisterElementIndices_>
	[[nodiscard]] constexpr inline OutRegister_ _make_identity_non_empty_register(std::index_sequence<RegisterElementIndices_...> register_element_indices_)
	{
		return EmuSIMD::setr<OutRegister_, Width_>
		(
			EmuCore::TMP::conditional_value_v<(RegisterElementIndices_ == OneIndex_), Value_, Value_(1), Value_(0)>...
		);
	}

	template<std::size_t MajorIndex_, std::size_t RegisterIndex_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto _make_identity_register()
		-> typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using _register_type = typename _fast_mat_uq::register_type;
		constexpr std::size_t min_index_in_register = RegisterIndex_ * _fast_mat_uq::num_elements_per_register;
		if constexpr (min_index_in_register <= MajorIndex_)
		{
			// If max_index > major_index, this doesn't contain the major's `1`.
			constexpr std::size_t max_index_in_register = (min_index_in_register + _fast_mat_uq::num_elements_per_register) - 1;
			if constexpr (max_index_in_register >= MajorIndex_)
			{
				constexpr std::size_t index_in_register = MajorIndex_ % _fast_mat_uq::num_elements_per_register;
				return _make_identity_non_empty_register<typename _fast_mat_uq::value_type, _register_type, _fast_mat_uq::per_element_width, index_in_register>
				(
					std::make_index_sequence<_fast_mat_uq::num_elements_per_register>()
				);
			}
			else
			{
				return EmuSIMD::setzero<typename _fast_mat_uq::register_type>();
			}
		}
		else
		{
			return EmuSIMD::setzero<typename _fast_mat_uq::register_type>();
		}
	}

	template<std::size_t MajorIndex_, EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...RegisterIndices_>
	[[nodiscard]] constexpr inline auto _make_identity_major_chunk()
		-> typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::major_chunk_type
	{
		if constexpr (sizeof...(RegisterIndices_) > 1)
		{
			return typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::major_chunk_type
			({
				_make_identity_register<MajorIndex_, RegisterIndices_, FastMatrix_>()...
			});
		}
		else
		{
			return _make_identity_register<MajorIndex_, 0, FastMatrix_>();
		}
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...MajorIndices_, std::size_t...RegisterIndices_>
	[[nodiscard]] constexpr inline auto _make_identity_matrix
	(
		std::index_sequence<MajorIndices_...> major_indices_,
		std::index_sequence<RegisterIndices_...> register_indices_
	) -> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		return typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
		(
			_make_identity_major_chunk<MajorIndices_, FastMatrix_, RegisterIndices_...>()...
		);
	}
#pragma endregion

	template<std::size_t MajorIndex_, std::size_t RegisterIndex_, EmuConcepts::EmuFastMatrix FastMatrix_>
	constexpr inline void _assign_identity_register(typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type* p_out_registers_)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		constexpr std::size_t major_offset = MajorIndex_ * _fast_mat_uq::num_registers_per_major;
		constexpr std::size_t offset = major_offset + RegisterIndex_;
		(*(p_out_registers_ + offset)) = _make_identity_register<MajorIndex_, RegisterIndex_, FastMatrix_>();
	}

	template<std::size_t MajorIndex_, EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...RegisterIndices_>
	constexpr inline void _assign_identity_major_chunk(typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type* p_out_registers_)
	{
		(
			_assign_identity_register<MajorIndex_, RegisterIndices_, FastMatrix_>
			(
				p_out_registers_
			), ...
		);
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...MajorIndices_, std::size_t...RegisterIndices_>
	constexpr inline void _assign_identity_matrix
	(
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type* p_out_registers_,
		std::index_sequence<MajorIndices_...> major_indices_,
		std::index_sequence<RegisterIndices_...> register_indices_
	)
	{
		(
			_assign_identity_major_chunk<MajorIndices_, FastMatrix_, RegisterIndices_...>
			(
				p_out_registers_
			), ...
		);
	}
}

#endif
